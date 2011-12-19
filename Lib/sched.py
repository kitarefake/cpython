"""A generally useful event scheduler class.

Each instance of this class manages its own queue.
No multi-threading is implied; you are supposed to hack that
yourself, or use a single instance per application.

Each instance is parametrized with two functions, one that is
supposed to return the current time, one that is supposed to
implement a delay.  You can implement real-time scheduling by
substituting time and sleep from built-in module time, or you can
implement simulated time by writing your own functions.  This can
also be used to integrate scheduling with STDWIN events; the delay
function is allowed to modify the queue.  Time can be expressed as
integers or floating point numbers, as long as it is consistent.

Events are specified by tuples (time, priority, action, argument).
As in UNIX, lower priority numbers mean higher priority; in this
way the queue can be maintained as a priority queue.  Execution of the
event means calling the action function, passing it the argument
sequence in "argument" (remember that in Python, multiple function
arguments are be packed in a sequence).
The action function may be an instance method so it
has another way to reference private data (besides global variables).
"""

# XXX The timefunc and delayfunc should have been defined as methods
# XXX so you can define new kinds of schedulers using subclassing
# XXX instead of having to define a module or class just to hold
# XXX the global state of your particular time and delay functions.

import time
import heapq
from collections import namedtuple
try:
    import threading
except ImportError:
    import dummy_threading as threading

__all__ = ["scheduler"]

class Event(namedtuple('Event', 'time, priority, action, argument, kwargs')):
    def __eq__(s, o): return (s.time, s.priority) == (o.time, o.priority)
    def __ne__(s, o): return (s.time, s.priority) != (o.time, o.priority)
    def __lt__(s, o): return (s.time, s.priority) <  (o.time, o.priority)
    def __le__(s, o): return (s.time, s.priority) <= (o.time, o.priority)
    def __gt__(s, o): return (s.time, s.priority) >  (o.time, o.priority)
    def __ge__(s, o): return (s.time, s.priority) >= (o.time, o.priority)

class scheduler:

    def __init__(self, timefunc=time.time, delayfunc=time.sleep):
        """Initialize a new instance, passing the time and delay
        functions"""
        self._queue = []
        self._lock = threading.RLock()
        self.timefunc = timefunc
        self.delayfunc = delayfunc

    def enterabs(self, time, priority, action, argument=[], kwargs={}):
        """Enter a new event in the queue at an absolute time.

        Returns an ID for the event which can be used to remove it,
        if necessary.

        """
        with self._lock:
            event = Event(time, priority, action, argument, kwargs)
            heapq.heappush(self._queue, event)
            return event # The ID

    def enter(self, delay, priority, action, argument=[], kwargs={}):
        """A variant that specifies the time as a relative time.

        This is actually the more commonly used interface.

        """
        with self._lock:
            time = self.timefunc() + delay
            return self.enterabs(time, priority, action, argument, kwargs)

    def cancel(self, event):
        """Remove an event from the queue.

        This must be presented the ID as returned by enter().
        If the event is not in the queue, this raises ValueError.

        """
        with self._lock:
            self._queue.remove(event)
            heapq.heapify(self._queue)

    def empty(self):
        """Check whether the queue is empty."""
        with self._lock:
            return not self._queue

    def run(self, blocking=True):
        """Execute events until the queue is empty.
        If blocking is False executes the scheduled events due to
        expire soonest (if any) and then return.

        When there is a positive delay until the first event, the
        delay function is called and the event is left in the queue;
        otherwise, the event is removed from the queue and executed
        (its action function is called, passing it the argument).  If
        the delay function returns prematurely, it is simply
        restarted.

        It is legal for both the delay function and the action
        function to modify the queue or to raise an exception;
        exceptions are not caught but the scheduler's state remains
        well-defined so run() may be called again.

        A questionable hack is added to allow other threads to run:
        just after an event is executed, a delay of 0 is executed, to
        avoid monopolizing the CPU when other threads are also
        runnable.

        """
        # localize variable access to minimize overhead
        # and to improve thread safety
        with self._lock:
            q = self._queue
            delayfunc = self.delayfunc
            timefunc = self.timefunc
            pop = heapq.heappop
            while q:
                time, priority, action, argument, kwargs = checked_event = q[0]
                now = timefunc()
                if now < time:
                    if not blocking:
                        return
                    delayfunc(time - now)
                else:
                    event = pop(q)
                    # Verify that the event was not removed or altered
                    # by another thread after we last looked at q[0].
                    if event is checked_event:
                        action(*argument, **kwargs)
                        delayfunc(0)   # Let other threads run
                    else:
                        heapq.heappush(q, event)

    @property
    def queue(self):
        """An ordered list of upcoming events.

        Events are named tuples with fields for:
            time, priority, action, arguments

        """
        # Use heapq to sort the queue rather than using 'sorted(self._queue)'.
        # With heapq, two events scheduled at the same time will show in
        # the actual order they would be retrieved.
        with self._lock:
            events = self._queue[:]
            return map(heapq.heappop, [events]*len(events))
