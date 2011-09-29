/* ------------------------------------------------------------------------

   unicodedata -- Provides access to the Unicode 5.2 data base.

   Data was extracted from the Unicode 5.2 UnicodeData.txt file.

   Written by Marc-Andre Lemburg (mal@lemburg.com).
   Modified for Python 2.0 by Fredrik Lundh (fredrik@pythonware.com)
   Modified by Martin v. Löwis (martin@v.loewis.de)

   Copyright (c) Corporation for National Research Initiatives.

   ------------------------------------------------------------------------ */

#include "Python.h"
#include "ucnhash.h"
#include "structmember.h"

/* character properties */

typedef struct {
    const unsigned char category;       /* index into
                                           _PyUnicode_CategoryNames */
    const unsigned char combining;      /* combining class value 0 - 255 */
    const unsigned char bidirectional;  /* index into
                                           _PyUnicode_BidirectionalNames */
    const unsigned char mirrored;       /* true if mirrored in bidir mode */
    const unsigned char east_asian_width;       /* index into
                                                   _PyUnicode_EastAsianWidth */
    const unsigned char normalization_quick_check; /* see is_normalized() */
} _PyUnicode_DatabaseRecord;

typedef struct change_record {
    /* sequence of fields should be the same as in merge_old_version */
    const unsigned char bidir_changed;
    const unsigned char category_changed;
    const unsigned char decimal_changed;
    const unsigned char mirrored_changed;
    const double numeric_changed;
} change_record;

/* data file generated by Tools/unicode/makeunicodedata.py */
#include "unicodedata_db.h"

static const _PyUnicode_DatabaseRecord*
_getrecord_ex(Py_UCS4 code)
{
    int index;
    if (code >= 0x110000)
        index = 0;
    else {
        index = index1[(code>>SHIFT)];
        index = index2[(index<<SHIFT)+(code&((1<<SHIFT)-1))];
    }

    return &_PyUnicode_Database_Records[index];
}

/* ------------- Previous-version API ------------------------------------- */
typedef struct previous_version {
    PyObject_HEAD
    const char *name;
    const change_record* (*getrecord)(Py_UCS4);
    Py_UCS4 (*normalization)(Py_UCS4);
} PreviousDBVersion;

#define get_old_record(self, v)    ((((PreviousDBVersion*)self)->getrecord)(v))

static PyMemberDef DB_members[] = {
        {"unidata_version", T_STRING, offsetof(PreviousDBVersion, name), READONLY},
        {NULL}
};

/* forward declaration */
static PyTypeObject UCD_Type;
#define UCD_Check(o) (Py_TYPE(o)==&UCD_Type)

static PyObject*
new_previous_version(const char*name, const change_record* (*getrecord)(Py_UCS4),
                     Py_UCS4 (*normalization)(Py_UCS4))
{
        PreviousDBVersion *self;
        self = PyObject_New(PreviousDBVersion, &UCD_Type);
        if (self == NULL)
                return NULL;
        self->name = name;
        self->getrecord = getrecord;
        self->normalization = normalization;
        return (PyObject*)self;
}


static Py_UCS4 getuchar(PyUnicodeObject *obj)
{
    if (PyUnicode_READY(obj))
        return (Py_UCS4)-1;
    if (PyUnicode_GET_LENGTH(obj) == 1) {
        if (PyUnicode_READY(obj))
            return (Py_UCS4)-1;
        return PyUnicode_READ_CHAR(obj, 0);
    }
    PyErr_SetString(PyExc_TypeError,
                    "need a single Unicode character as parameter");
    return (Py_UCS4)-1;
}

/* --- Module API --------------------------------------------------------- */

PyDoc_STRVAR(unicodedata_decimal__doc__,
"decimal(unichr[, default])\n\
\n\
Returns the decimal value assigned to the Unicode character unichr\n\
as integer. If no such value is defined, default is returned, or, if\n\
not given, ValueError is raised.");

static PyObject *
unicodedata_decimal(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    PyObject *defobj = NULL;
    int have_old = 0;
    long rc;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!|O:decimal", &PyUnicode_Type, &v, &defobj))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;

    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0) {
            /* unassigned */
            have_old = 1;
            rc = -1;
        }
        else if (old->decimal_changed != 0xFF) {
            have_old = 1;
            rc = old->decimal_changed;
        }
    }

    if (!have_old)
        rc = Py_UNICODE_TODECIMAL(c);
    if (rc < 0) {
        if (defobj == NULL) {
            PyErr_SetString(PyExc_ValueError,
                            "not a decimal");
            return NULL;
        }
        else {
            Py_INCREF(defobj);
            return defobj;
        }
    }
    return PyLong_FromLong(rc);
}

PyDoc_STRVAR(unicodedata_digit__doc__,
"digit(unichr[, default])\n\
\n\
Returns the digit value assigned to the Unicode character unichr as\n\
integer. If no such value is defined, default is returned, or, if\n\
not given, ValueError is raised.");

static PyObject *
unicodedata_digit(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    PyObject *defobj = NULL;
    long rc;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!|O:digit", &PyUnicode_Type, &v, &defobj))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;
    rc = Py_UNICODE_TODIGIT(c);
    if (rc < 0) {
        if (defobj == NULL) {
            PyErr_SetString(PyExc_ValueError, "not a digit");
            return NULL;
        }
        else {
            Py_INCREF(defobj);
            return defobj;
        }
    }
    return PyLong_FromLong(rc);
}

PyDoc_STRVAR(unicodedata_numeric__doc__,
"numeric(unichr[, default])\n\
\n\
Returns the numeric value assigned to the Unicode character unichr\n\
as float. If no such value is defined, default is returned, or, if\n\
not given, ValueError is raised.");

static PyObject *
unicodedata_numeric(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    PyObject *defobj = NULL;
    int have_old = 0;
    double rc;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!|O:numeric", &PyUnicode_Type, &v, &defobj))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;

    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0) {
            /* unassigned */
            have_old = 1;
            rc = -1.0;
        }
        else if (old->decimal_changed != 0xFF) {
            have_old = 1;
            rc = old->decimal_changed;
        }
    }

    if (!have_old)
        rc = Py_UNICODE_TONUMERIC(c);
    if (rc == -1.0) {
        if (defobj == NULL) {
            PyErr_SetString(PyExc_ValueError, "not a numeric character");
            return NULL;
        }
        else {
            Py_INCREF(defobj);
            return defobj;
        }
    }
    return PyFloat_FromDouble(rc);
}

PyDoc_STRVAR(unicodedata_category__doc__,
"category(unichr)\n\
\n\
Returns the general category assigned to the Unicode character\n\
unichr as string.");

static PyObject *
unicodedata_category(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    int index;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!:category",
                          &PyUnicode_Type, &v))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;
    index = (int) _getrecord_ex(c)->category;
    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed != 0xFF)
            index = old->category_changed;
    }
    return PyUnicode_FromString(_PyUnicode_CategoryNames[index]);
}

PyDoc_STRVAR(unicodedata_bidirectional__doc__,
"bidirectional(unichr)\n\
\n\
Returns the bidirectional category assigned to the Unicode character\n\
unichr as string. If no such value is defined, an empty string is\n\
returned.");

static PyObject *
unicodedata_bidirectional(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    int index;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!:bidirectional",
                          &PyUnicode_Type, &v))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;
    index = (int) _getrecord_ex(c)->bidirectional;
    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0)
            index = 0; /* unassigned */
        else if (old->bidir_changed != 0xFF)
            index = old->bidir_changed;
    }
    return PyUnicode_FromString(_PyUnicode_BidirectionalNames[index]);
}

PyDoc_STRVAR(unicodedata_combining__doc__,
"combining(unichr)\n\
\n\
Returns the canonical combining class assigned to the Unicode\n\
character unichr as integer. Returns 0 if no combining class is\n\
defined.");

static PyObject *
unicodedata_combining(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    int index;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!:combining",
                          &PyUnicode_Type, &v))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;
    index = (int) _getrecord_ex(c)->combining;
    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0)
            index = 0; /* unassigned */
    }
    return PyLong_FromLong(index);
}

PyDoc_STRVAR(unicodedata_mirrored__doc__,
"mirrored(unichr)\n\
\n\
Returns the mirrored property assigned to the Unicode character\n\
unichr as integer. Returns 1 if the character has been identified as\n\
a \"mirrored\" character in bidirectional text, 0 otherwise.");

static PyObject *
unicodedata_mirrored(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    int index;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!:mirrored",
                          &PyUnicode_Type, &v))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;
    index = (int) _getrecord_ex(c)->mirrored;
    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0)
            index = 0; /* unassigned */
        else if (old->mirrored_changed != 0xFF)
            index = old->mirrored_changed;
    }
    return PyLong_FromLong(index);
}

PyDoc_STRVAR(unicodedata_east_asian_width__doc__,
"east_asian_width(unichr)\n\
\n\
Returns the east asian width assigned to the Unicode character\n\
unichr as string.");

static PyObject *
unicodedata_east_asian_width(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    int index;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!:east_asian_width",
                          &PyUnicode_Type, &v))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;
    index = (int) _getrecord_ex(c)->east_asian_width;
    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0)
            index = 0; /* unassigned */
    }
    return PyUnicode_FromString(_PyUnicode_EastAsianWidthNames[index]);
}

PyDoc_STRVAR(unicodedata_decomposition__doc__,
"decomposition(unichr)\n\
\n\
Returns the character decomposition mapping assigned to the Unicode\n\
character unichr as string. An empty string is returned in case no\n\
such mapping is defined.");

static PyObject *
unicodedata_decomposition(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    char decomp[256];
    int code, index, count;
    size_t i;
    unsigned int prefix_index;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!:decomposition",
                          &PyUnicode_Type, &v))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;

    code = (int)c;

    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0)
            return PyUnicode_FromString(""); /* unassigned */
    }

    if (code < 0 || code >= 0x110000)
        index = 0;
    else {
        index = decomp_index1[(code>>DECOMP_SHIFT)];
        index = decomp_index2[(index<<DECOMP_SHIFT)+
                             (code&((1<<DECOMP_SHIFT)-1))];
    }

    /* high byte is number of hex bytes (usually one or two), low byte
       is prefix code (from*/
    count = decomp_data[index] >> 8;

    /* XXX: could allocate the PyString up front instead
       (strlen(prefix) + 5 * count + 1 bytes) */

    /* Based on how index is calculated above and decomp_data is generated
       from Tools/unicode/makeunicodedata.py, it should not be possible
       to overflow decomp_prefix. */
    prefix_index = decomp_data[index] & 255;
    assert(prefix_index < Py_ARRAY_LENGTH(decomp_prefix));

    /* copy prefix */
    i = strlen(decomp_prefix[prefix_index]);
    memcpy(decomp, decomp_prefix[prefix_index], i);

    while (count-- > 0) {
        if (i)
            decomp[i++] = ' ';
        assert(i < sizeof(decomp));
        PyOS_snprintf(decomp + i, sizeof(decomp) - i, "%04X",
                      decomp_data[++index]);
        i += strlen(decomp + i);
    }
    return PyUnicode_FromStringAndSize(decomp, i);
}

static void
get_decomp_record(PyObject *self, Py_UCS4 code, int *index, int *prefix, int *count)
{
    if (code >= 0x110000) {
        *index = 0;
    } else if (self && UCD_Check(self) &&
               get_old_record(self, code)->category_changed==0) {
        /* unassigned in old version */
        *index = 0;
    }
    else {
        *index = decomp_index1[(code>>DECOMP_SHIFT)];
        *index = decomp_index2[(*index<<DECOMP_SHIFT)+
                               (code&((1<<DECOMP_SHIFT)-1))];
    }

    /* high byte is number of hex bytes (usually one or two), low byte
       is prefix code (from*/
    *count = decomp_data[*index] >> 8;
    *prefix = decomp_data[*index] & 255;

    (*index)++;
}

#define SBase   0xAC00
#define LBase   0x1100
#define VBase   0x1161
#define TBase   0x11A7
#define LCount  19
#define VCount  21
#define TCount  28
#define NCount  (VCount*TCount)
#define SCount  (LCount*NCount)

static PyObject*
nfd_nfkd(PyObject *self, PyObject *input, int k)
{
    PyObject *result;
    Py_UCS4 *output;
    Py_ssize_t i, o, osize;
    int kind;
    void *data;
    /* Longest decomposition in Unicode 3.2: U+FDFA */
    Py_UCS4 stack[20];
    Py_ssize_t space, isize;
    int index, prefix, count, stackptr;
    unsigned char prev, cur;

    stackptr = 0;
    isize = PyUnicode_GET_LENGTH(input);
    /* Overallocate atmost 10 characters. */
    space = (isize > 10 ? 10 : isize) + isize;
    osize = space;
    output = PyMem_Malloc(space * sizeof(Py_UCS4));
    if (!output) {
        PyErr_NoMemory();
        return NULL;
    }
    i = o = 0;
    kind = PyUnicode_KIND(input);
    data = PyUnicode_DATA(input);

    while (i < isize) {
        stack[stackptr++] = PyUnicode_READ(kind, data, i++);
        while(stackptr) {
            Py_UCS4 code = stack[--stackptr];
            /* Hangul Decomposition adds three characters in
               a single step, so we need atleast that much room. */
            if (space < 3) {
                osize += 10;
                space += 10;
                output = PyMem_Realloc(output, osize*sizeof(Py_UCS4));
                if (output == NULL) {
                    PyErr_NoMemory();
                    return NULL;
                }
            }
            /* Hangul Decomposition. */
            if (SBase <= code && code < (SBase+SCount)) {
                int SIndex = code - SBase;
                int L = LBase + SIndex / NCount;
                int V = VBase + (SIndex % NCount) / TCount;
                int T = TBase + SIndex % TCount;
                output[o++] = L;
                output[o++] = V;
                space -= 2;
                if (T != TBase) {
                    output[o++] = T;
                    space --;
                }
                continue;
            }
            /* normalization changes */
            if (self && UCD_Check(self)) {
                Py_UCS4 value = ((PreviousDBVersion*)self)->normalization(code);
                if (value != 0) {
                    stack[stackptr++] = value;
                    continue;
                }
            }

            /* Other decompositions. */
            get_decomp_record(self, code, &index, &prefix, &count);

            /* Copy character if it is not decomposable, or has a
               compatibility decomposition, but we do NFD. */
            if (!count || (prefix && !k)) {
                output[o++] = code;
                space--;
                continue;
            }
            /* Copy decomposition onto the stack, in reverse
               order.  */
            while(count) {
                code = decomp_data[index + (--count)];
                stack[stackptr++] = code;
            }
        }
    }

    result = PyUnicode_FromKindAndData(PyUnicode_4BYTE_KIND,
                                       output, o);
    PyMem_Free(output);
    if (!result)
        return NULL;
    /* result is guaranteed to be ready, as it is compact. */
    kind = PyUnicode_KIND(result);
    data = PyUnicode_DATA(result);

    /* Sort canonically. */
    i = 0;
    prev = _getrecord_ex(PyUnicode_READ(kind, data, i))->combining;
    for (i++; i < PyUnicode_GET_LENGTH(result); i++) {
        cur = _getrecord_ex(PyUnicode_READ(kind, data, i))->combining;
        if (prev == 0 || cur == 0 || prev <= cur) {
            prev = cur;
            continue;
        }
        /* Non-canonical order. Need to switch *i with previous. */
        o = i - 1;
        while (1) {
            Py_UCS4 tmp = PyUnicode_READ(kind, data, o+1);
            PyUnicode_WRITE(kind, data, o+1,
                            PyUnicode_READ(kind, data, o));
            PyUnicode_WRITE(kind, data, o, tmp);
            o--;
            if (o < 0)
                break;
            prev = _getrecord_ex(PyUnicode_READ(kind, data, o))->combining;
            if (prev == 0 || prev <= cur)
                break;
        }
        prev = _getrecord_ex(PyUnicode_READ(kind, data, i))->combining;
    }
    return result;
}

static int
find_nfc_index(PyObject *self, struct reindex* nfc, Py_UCS4 code)
{
    int index;
    for (index = 0; nfc[index].start; index++) {
        int start = nfc[index].start;
        if (code < start)
            return -1;
        if (code <= start + nfc[index].count) {
            int delta = code - start;
            return nfc[index].index + delta;
        }
    }
    return -1;
}

static PyObject*
nfc_nfkc(PyObject *self, PyObject *input, int k)
{
    PyObject *result;
    int kind;
    void *data;
    Py_UCS4 *output;
    Py_ssize_t i, i1, o, len;
    int f,l,index,index1,comb;
    Py_UCS4 code;
    Py_ssize_t skipped[20];
    int cskipped = 0;

    result = nfd_nfkd(self, input, k);
    if (!result)
        return NULL;
    /* result will be "ready". */
    kind = PyUnicode_KIND(result);
    data = PyUnicode_DATA(result);
    len = PyUnicode_GET_LENGTH(result);

    /* We allocate a buffer for the output.
       If we find that we made no changes, we still return
       the NFD result. */
    output = PyMem_Malloc(len * sizeof(Py_UCS4));
    if (!output) {
        PyErr_NoMemory();
        Py_DECREF(result);
        return 0;
    }
    i = o = 0;

  again:
    while (i < len) {
      for (index = 0; index < cskipped; index++) {
          if (skipped[index] == i) {
              /* *i character is skipped.
                 Remove from list. */
              skipped[index] = skipped[cskipped-1];
              cskipped--;
              i++;
              goto again; /* continue while */
          }
      }
      /* Hangul Composition. We don't need to check for <LV,T>
         pairs, since we always have decomposed data. */
      code = PyUnicode_READ(kind, data, i);
      if (LBase <= code && code < (LBase+LCount) &&
          i + 1 < len &&
          VBase <= PyUnicode_READ(kind, data, i+1) &&
          PyUnicode_READ(kind, data, i+1) <= (VBase+VCount)) {
          int LIndex, VIndex;
          LIndex = code - LBase;
          VIndex = PyUnicode_READ(kind, data, i+1) - VBase;
          code = SBase + (LIndex*VCount+VIndex)*TCount;
          i+=2;
          if (i < len &&
              TBase <= PyUnicode_READ(kind, data, i) &&
              PyUnicode_READ(kind, data, i) <= (TBase+TCount)) {
              code += PyUnicode_READ(kind, data, i)-TBase;
              i++;
          }
          output[o++] = code;
          continue;
      }

      /* code is still input[i] here */
      f = find_nfc_index(self, nfc_first, code);
      if (f == -1) {
          output[o++] = code;
          i++;
          continue;
      }
      /* Find next unblocked character. */
      i1 = i+1;
      comb = 0;
      /* output base character for now; might be updated later. */
      output[o] = PyUnicode_READ(kind, data, i);
      while (i1 < len) {
          Py_UCS4 code1 = PyUnicode_READ(kind, data, i1);
          int comb1 = _getrecord_ex(code1)->combining;
          if (comb) {
              if (comb1 == 0)
                  break;
              if (comb >= comb1) {
                  /* Character is blocked. */
                  i1++;
                  continue;
              }
          }
          l = find_nfc_index(self, nfc_last, code1);
          /* i1 cannot be combined with i. If i1
             is a starter, we don't need to look further.
             Otherwise, record the combining class. */
          if (l == -1) {
            not_combinable:
              if (comb1 == 0)
                  break;
              comb = comb1;
              i1++;
              continue;
          }
          index = f*TOTAL_LAST + l;
          index1 = comp_index[index >> COMP_SHIFT];
          code = comp_data[(index1<<COMP_SHIFT)+
                           (index&((1<<COMP_SHIFT)-1))];
          if (code == 0)
              goto not_combinable;

          /* Replace the original character. */
          output[o] = code;
          /* Mark the second character unused. */
          assert(cskipped < 20);
          skipped[cskipped++] = i1;
          i1++;
          f = find_nfc_index(self, nfc_first, output[o]);
          if (f == -1)
              break;
      }
      /* Output character was already written.
         Just advance the indices. */
      o++; i++;
    }
    if (o == len) {
        /* No changes. Return original string. */
        PyMem_Free(output);
        return result;
    }
    Py_DECREF(result);
    result = PyUnicode_FromKindAndData(PyUnicode_4BYTE_KIND,
                                       output, o);
    PyMem_Free(output);
    return result;
}

/* Return 1 if the input is certainly normalized, 0 if it might not be. */
static int
is_normalized(PyObject *self, PyObject *input, int nfc, int k)
{
    Py_ssize_t i, len;
    int kind;
    void *data;
    unsigned char prev_combining = 0, quickcheck_mask;

    /* An older version of the database is requested, quickchecks must be
       disabled. */
    if (self && UCD_Check(self))
        return 0;

    /* The two quickcheck bits at this shift mean 0=Yes, 1=Maybe, 2=No,
       as described in http://unicode.org/reports/tr15/#Annex8. */
    quickcheck_mask = 3 << ((nfc ? 4 : 0) + (k ? 2 : 0));

    i = 0;
    kind = PyUnicode_KIND(input);
    data = PyUnicode_DATA(input);
    len = PyUnicode_GET_LENGTH(input);
    while (i < len) {
        Py_UCS4 ch = PyUnicode_READ(kind, data, i++);
        const _PyUnicode_DatabaseRecord *record = _getrecord_ex(ch);
        unsigned char combining = record->combining;
        unsigned char quickcheck = record->normalization_quick_check;

        if (quickcheck & quickcheck_mask)
            return 0; /* this string might need normalization */
        if (combining && prev_combining > combining)
            return 0; /* non-canonical sort order, not normalized */
        prev_combining = combining;
    }
    return 1; /* certainly normalized */
}

PyDoc_STRVAR(unicodedata_normalize__doc__,
"normalize(form, unistr)\n\
\n\
Return the normal form 'form' for the Unicode string unistr.  Valid\n\
values for form are 'NFC', 'NFKC', 'NFD', and 'NFKD'.");

static PyObject*
unicodedata_normalize(PyObject *self, PyObject *args)
{
    char *form;
    PyObject *input;

    if(!PyArg_ParseTuple(args, "sO!:normalize",
                         &form, &PyUnicode_Type, &input))
        return NULL;

    if (PyUnicode_READY(input) == -1)
        return NULL;

    if (PyUnicode_GET_LENGTH(input) == 0) {
        /* Special case empty input strings, since resizing
           them  later would cause internal errors. */
        Py_INCREF(input);
        return input;
    }

    if (strcmp(form, "NFC") == 0) {
        if (is_normalized(self, input, 1, 0)) {
            Py_INCREF(input);
            return input;
        }
        return nfc_nfkc(self, input, 0);
    }
    if (strcmp(form, "NFKC") == 0) {
        if (is_normalized(self, input, 1, 1)) {
            Py_INCREF(input);
            return input;
        }
        return nfc_nfkc(self, input, 1);
    }
    if (strcmp(form, "NFD") == 0) {
        if (is_normalized(self, input, 0, 0)) {
            Py_INCREF(input);
            return input;
        }
        return nfd_nfkd(self, input, 0);
    }
    if (strcmp(form, "NFKD") == 0) {
        if (is_normalized(self, input, 0, 1)) {
            Py_INCREF(input);
            return input;
        }
        return nfd_nfkd(self, input, 1);
    }
    PyErr_SetString(PyExc_ValueError, "invalid normalization form");
    return NULL;
}

/* -------------------------------------------------------------------- */
/* unicode character name tables */

/* data file generated by Tools/unicode/makeunicodedata.py */
#include "unicodename_db.h"

/* -------------------------------------------------------------------- */
/* database code (cut and pasted from the unidb package) */

static unsigned long
_gethash(const char *s, int len, int scale)
{
    int i;
    unsigned long h = 0;
    unsigned long ix;
    for (i = 0; i < len; i++) {
        h = (h * scale) + (unsigned char) toupper(Py_CHARMASK(s[i]));
        ix = h & 0xff000000;
        if (ix)
            h = (h ^ ((ix>>24) & 0xff)) & 0x00ffffff;
    }
    return h;
}

static char *hangul_syllables[][3] = {
    { "G",  "A",   ""   },
    { "GG", "AE",  "G"  },
    { "N",  "YA",  "GG" },
    { "D",  "YAE", "GS" },
    { "DD", "EO",  "N", },
    { "R",  "E",   "NJ" },
    { "M",  "YEO", "NH" },
    { "B",  "YE",  "D"  },
    { "BB", "O",   "L"  },
    { "S",  "WA",  "LG" },
    { "SS", "WAE", "LM" },
    { "",   "OE",  "LB" },
    { "J",  "YO",  "LS" },
    { "JJ", "U",   "LT" },
    { "C",  "WEO", "LP" },
    { "K",  "WE",  "LH" },
    { "T",  "WI",  "M"  },
    { "P",  "YU",  "B"  },
    { "H",  "EU",  "BS" },
    { 0,    "YI",  "S"  },
    { 0,    "I",   "SS" },
    { 0,    0,     "NG" },
    { 0,    0,     "J"  },
    { 0,    0,     "C"  },
    { 0,    0,     "K"  },
    { 0,    0,     "T"  },
    { 0,    0,     "P"  },
    { 0,    0,     "H"  }
};

/* These ranges need to match makeunicodedata.py:cjk_ranges. */
static int
is_unified_ideograph(Py_UCS4 code)
{
    return
        (0x3400 <= code && code <= 0x4DB5)   || /* CJK Ideograph Extension A */
        (0x4E00 <= code && code <= 0x9FCB)   || /* CJK Ideograph */
        (0x20000 <= code && code <= 0x2A6D6) || /* CJK Ideograph Extension B */
        (0x2A700 <= code && code <= 0x2B734) || /* CJK Ideograph Extension C */
        (0x2B740 <= code && code <= 0x2B81D);   /* CJK Ideograph Extension D */
}

static int
_getucname(PyObject *self, Py_UCS4 code, char* buffer, int buflen)
{
    int offset;
    int i;
    int word;
    unsigned char* w;

    if (code >= 0x110000)
        return 0;

    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, code);
        if (old->category_changed == 0) {
            /* unassigned */
            return 0;
        }
    }

    if (SBase <= code && code < SBase+SCount) {
        /* Hangul syllable. */
        int SIndex = code - SBase;
        int L = SIndex / NCount;
        int V = (SIndex % NCount) / TCount;
        int T = SIndex % TCount;

        if (buflen < 27)
            /* Worst case: HANGUL SYLLABLE <10chars>. */
            return 0;
        strcpy(buffer, "HANGUL SYLLABLE ");
        buffer += 16;
        strcpy(buffer, hangul_syllables[L][0]);
        buffer += strlen(hangul_syllables[L][0]);
        strcpy(buffer, hangul_syllables[V][1]);
        buffer += strlen(hangul_syllables[V][1]);
        strcpy(buffer, hangul_syllables[T][2]);
        buffer += strlen(hangul_syllables[T][2]);
        *buffer = '\0';
        return 1;
    }

    if (is_unified_ideograph(code)) {
        if (buflen < 28)
            /* Worst case: CJK UNIFIED IDEOGRAPH-20000 */
            return 0;
        sprintf(buffer, "CJK UNIFIED IDEOGRAPH-%X", code);
        return 1;
    }

    /* get offset into phrasebook */
    offset = phrasebook_offset1[(code>>phrasebook_shift)];
    offset = phrasebook_offset2[(offset<<phrasebook_shift) +
                               (code&((1<<phrasebook_shift)-1))];
    if (!offset)
        return 0;

    i = 0;

    for (;;) {
        /* get word index */
        word = phrasebook[offset] - phrasebook_short;
        if (word >= 0) {
            word = (word << 8) + phrasebook[offset+1];
            offset += 2;
        } else
            word = phrasebook[offset++];
        if (i) {
            if (i > buflen)
                return 0; /* buffer overflow */
            buffer[i++] = ' ';
        }
        /* copy word string from lexicon.  the last character in the
           word has bit 7 set.  the last word in a string ends with
           0x80 */
        w = lexicon + lexicon_offset[word];
        while (*w < 128) {
            if (i >= buflen)
                return 0; /* buffer overflow */
            buffer[i++] = *w++;
        }
        if (i >= buflen)
            return 0; /* buffer overflow */
        buffer[i++] = *w & 127;
        if (*w == 128)
            break; /* end of word */
    }

    return 1;
}

static int
_cmpname(PyObject *self, int code, const char* name, int namelen)
{
    /* check if code corresponds to the given name */
    int i;
    char buffer[NAME_MAXLEN];
    if (!_getucname(self, code, buffer, sizeof(buffer)))
        return 0;
    for (i = 0; i < namelen; i++) {
        if (toupper(Py_CHARMASK(name[i])) != buffer[i])
            return 0;
    }
    return buffer[namelen] == '\0';
}

static void
find_syllable(const char *str, int *len, int *pos, int count, int column)
{
    int i, len1;
    *len = -1;
    for (i = 0; i < count; i++) {
        char *s = hangul_syllables[i][column];
        len1 = strlen(s);
        if (len1 <= *len)
            continue;
        if (strncmp(str, s, len1) == 0) {
            *len = len1;
            *pos = i;
        }
    }
    if (*len == -1) {
        *len = 0;
    }
}

static int
_getcode(PyObject* self, const char* name, int namelen, Py_UCS4* code)
{
    unsigned int h, v;
    unsigned int mask = code_size-1;
    unsigned int i, incr;

    /* Check for hangul syllables. */
    if (strncmp(name, "HANGUL SYLLABLE ", 16) == 0) {
        int len, L = -1, V = -1, T = -1;
        const char *pos = name + 16;
        find_syllable(pos, &len, &L, LCount, 0);
        pos += len;
        find_syllable(pos, &len, &V, VCount, 1);
        pos += len;
        find_syllable(pos, &len, &T, TCount, 2);
        pos += len;
        if (L != -1 && V != -1 && T != -1 && pos-name == namelen) {
            *code = SBase + (L*VCount+V)*TCount + T;
            return 1;
        }
        /* Otherwise, it's an illegal syllable name. */
        return 0;
    }

    /* Check for unified ideographs. */
    if (strncmp(name, "CJK UNIFIED IDEOGRAPH-", 22) == 0) {
        /* Four or five hexdigits must follow. */
        v = 0;
        name += 22;
        namelen -= 22;
        if (namelen != 4 && namelen != 5)
            return 0;
        while (namelen--) {
            v *= 16;
            if (*name >= '0' && *name <= '9')
                v += *name - '0';
            else if (*name >= 'A' && *name <= 'F')
                v += *name - 'A' + 10;
            else
                return 0;
            name++;
        }
        if (!is_unified_ideograph(v))
            return 0;
        *code = v;
        return 1;
    }

    /* the following is the same as python's dictionary lookup, with
       only minor changes.  see the makeunicodedata script for more
       details */

    h = (unsigned int) _gethash(name, namelen, code_magic);
    i = (~h) & mask;
    v = code_hash[i];
    if (!v)
        return 0;
    if (_cmpname(self, v, name, namelen)) {
        *code = v;
        return 1;
    }
    incr = (h ^ (h >> 3)) & mask;
    if (!incr)
        incr = mask;
    for (;;) {
        i = (i + incr) & mask;
        v = code_hash[i];
        if (!v)
            return 0;
        if (_cmpname(self, v, name, namelen)) {
            *code = v;
            return 1;
        }
        incr = incr << 1;
        if (incr > mask)
            incr = incr ^ code_poly;
    }
}

static const _PyUnicode_Name_CAPI hashAPI =
{
    sizeof(_PyUnicode_Name_CAPI),
    _getucname,
    _getcode
};

/* -------------------------------------------------------------------- */
/* Python bindings */

PyDoc_STRVAR(unicodedata_name__doc__,
"name(unichr[, default])\n\
Returns the name assigned to the Unicode character unichr as a\n\
string. If no name is defined, default is returned, or, if not\n\
given, ValueError is raised.");

static PyObject *
unicodedata_name(PyObject* self, PyObject* args)
{
    char name[NAME_MAXLEN];
    Py_UCS4 c;

    PyUnicodeObject* v;
    PyObject* defobj = NULL;
    if (!PyArg_ParseTuple(args, "O!|O:name", &PyUnicode_Type, &v, &defobj))
        return NULL;

    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;

    if (!_getucname(self, c, name, sizeof(name))) {
        if (defobj == NULL) {
            PyErr_SetString(PyExc_ValueError, "no such name");
            return NULL;
        }
        else {
            Py_INCREF(defobj);
            return defobj;
        }
    }

    return PyUnicode_FromString(name);
}

PyDoc_STRVAR(unicodedata_lookup__doc__,
"lookup(name)\n\
\n\
Look up character by name.  If a character with the\n\
given name is found, return the corresponding Unicode\n\
character.  If not found, KeyError is raised.");

static PyObject *
unicodedata_lookup(PyObject* self, PyObject* args)
{
    Py_UCS4 code;

    char* name;
    int namelen;
    if (!PyArg_ParseTuple(args, "s#:lookup", &name, &namelen))
        return NULL;

    if (!_getcode(self, name, namelen, &code)) {
        PyErr_Format(PyExc_KeyError, "undefined character name '%s'",
                     name);
        return NULL;
    }

    return PyUnicode_FromOrdinal(code);
}

/* XXX Add doc strings. */

static PyMethodDef unicodedata_functions[] = {
    {"decimal", unicodedata_decimal, METH_VARARGS, unicodedata_decimal__doc__},
    {"digit", unicodedata_digit, METH_VARARGS, unicodedata_digit__doc__},
    {"numeric", unicodedata_numeric, METH_VARARGS, unicodedata_numeric__doc__},
    {"category", unicodedata_category, METH_VARARGS,
                 unicodedata_category__doc__},
    {"bidirectional", unicodedata_bidirectional, METH_VARARGS,
                      unicodedata_bidirectional__doc__},
    {"combining", unicodedata_combining, METH_VARARGS,
                  unicodedata_combining__doc__},
    {"mirrored", unicodedata_mirrored, METH_VARARGS,
                 unicodedata_mirrored__doc__},
    {"east_asian_width", unicodedata_east_asian_width, METH_VARARGS,
                         unicodedata_east_asian_width__doc__},
    {"decomposition", unicodedata_decomposition, METH_VARARGS,
                      unicodedata_decomposition__doc__},
    {"name", unicodedata_name, METH_VARARGS, unicodedata_name__doc__},
    {"lookup", unicodedata_lookup, METH_VARARGS, unicodedata_lookup__doc__},
    {"normalize", unicodedata_normalize, METH_VARARGS,
                  unicodedata_normalize__doc__},
    {NULL, NULL}                /* sentinel */
};

static PyTypeObject UCD_Type = {
        /* The ob_type field must be initialized in the module init function
         * to be portable to Windows without using C++. */
        PyVarObject_HEAD_INIT(NULL, 0)
        "unicodedata.UCD",              /*tp_name*/
        sizeof(PreviousDBVersion),      /*tp_basicsize*/
        0,                      /*tp_itemsize*/
        /* methods */
        (destructor)PyObject_Del, /*tp_dealloc*/
        0,                      /*tp_print*/
        0,                      /*tp_getattr*/
        0,                      /*tp_setattr*/
        0,                      /*tp_reserved*/
        0,                      /*tp_repr*/
        0,                      /*tp_as_number*/
        0,                      /*tp_as_sequence*/
        0,                      /*tp_as_mapping*/
        0,                      /*tp_hash*/
        0,                      /*tp_call*/
        0,                      /*tp_str*/
        PyObject_GenericGetAttr,/*tp_getattro*/
        0,                      /*tp_setattro*/
        0,                      /*tp_as_buffer*/
        Py_TPFLAGS_DEFAULT,     /*tp_flags*/
        0,                      /*tp_doc*/
        0,                      /*tp_traverse*/
        0,                      /*tp_clear*/
        0,                      /*tp_richcompare*/
        0,                      /*tp_weaklistoffset*/
        0,                      /*tp_iter*/
        0,                      /*tp_iternext*/
        unicodedata_functions,  /*tp_methods*/
        DB_members,             /*tp_members*/
        0,                      /*tp_getset*/
        0,                      /*tp_base*/
        0,                      /*tp_dict*/
        0,                      /*tp_descr_get*/
        0,                      /*tp_descr_set*/
        0,                      /*tp_dictoffset*/
        0,                      /*tp_init*/
        0,                      /*tp_alloc*/
        0,                      /*tp_new*/
        0,                      /*tp_free*/
        0,                      /*tp_is_gc*/
};

PyDoc_STRVAR(unicodedata_docstring,
"This module provides access to the Unicode Character Database which\n\
defines character properties for all Unicode characters. The data in\n\
this database is based on the UnicodeData.txt file version\n\
5.2.0 which is publically available from ftp://ftp.unicode.org/.\n\
\n\
The module uses the same names and symbols as defined by the\n\
UnicodeData File Format 5.2.0 (see\n\
http://www.unicode.org/reports/tr44/tr44-4.html).");


static struct PyModuleDef unicodedatamodule = {
        PyModuleDef_HEAD_INIT,
        "unicodedata",
        unicodedata_docstring,
        -1,
        unicodedata_functions,
        NULL,
        NULL,
        NULL,
        NULL
};

PyMODINIT_FUNC
PyInit_unicodedata(void)
{
    PyObject *m, *v;

    Py_TYPE(&UCD_Type) = &PyType_Type;

    m = PyModule_Create(&unicodedatamodule);
    if (!m)
        return NULL;

    PyModule_AddStringConstant(m, "unidata_version", UNIDATA_VERSION);
    Py_INCREF(&UCD_Type);
    PyModule_AddObject(m, "UCD", (PyObject*)&UCD_Type);

    /* Previous versions */
    v = new_previous_version("3.2.0", get_change_3_2_0, normalization_3_2_0);
    if (v != NULL)
        PyModule_AddObject(m, "ucd_3_2_0", v);

    /* Export C API */
    v = PyCapsule_New((void *)&hashAPI, PyUnicodeData_CAPSULE_NAME, NULL);
    if (v != NULL)
        PyModule_AddObject(m, "ucnhash_CAPI", v);
    return m;
}

/*
Local variables:
c-basic-offset: 4
indent-tabs-mode: nil
End:
*/
