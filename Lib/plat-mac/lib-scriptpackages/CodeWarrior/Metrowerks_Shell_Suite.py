"""Suite Metrowerks Shell Suite: Events supported by the Metrowerks Project Shell
Level 1, version 1

Generated from /Volumes/Moes/Applications (Mac OS 9)/Metrowerks CodeWarrior 7.0/Metrowerks CodeWarrior/CodeWarrior IDE 4.2.6
AETE/AEUT resource version 1/0, language 0, script 0
"""

import aetools
import MacOS

_code = 'MMPR'

class Metrowerks_Shell_Suite_Events:

	_argmap_Add_Files = {
		'To_Segment' : 'Segm',
	}

	def Add_Files(self, _object, _attributes={}, **_arguments):
		"""Add Files: Add the specified file(s) to the current project
		Required argument: List of files to add
		Keyword argument To_Segment: Segment number into which to add the file(s)
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Error code for each file added
		"""
		_code = 'MMPR'
		_subcode = 'AddF'

		aetools.keysubst(_arguments, self._argmap_Add_Files)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Check_Syntax = {
		'ExternalEditor' : 'Errs',
	}

	def Check_Syntax(self, _object, _attributes={}, **_arguments):
		"""Check Syntax: Check the syntax of the specified file(s)
		Required argument: List of files to check the syntax of
		Keyword argument ExternalEditor: Should the contents of the message window be returned to the caller?
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Errors for each file whose syntax was checked
		"""
		_code = 'MMPR'
		_subcode = 'Chek'

		aetools.keysubst(_arguments, self._argmap_Check_Syntax)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Close_Project(self, _no_object=None, _attributes={}, **_arguments):
		"""Close Project: Close the current project
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'ClsP'

		if _arguments: raise TypeError, 'No optional args expected'
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Close_Window = {
		'Saving' : 'savo',
	}

	def Close_Window(self, _object, _attributes={}, **_arguments):
		"""Close Window: Close the windows showing the specified files
		Required argument: The files to close
		Keyword argument Saving: Whether to save changes to each file before closing its window
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'ClsW'

		aetools.keysubst(_arguments, self._argmap_Close_Window)
		_arguments['----'] = _object

		aetools.enumsubst(_arguments, 'savo', _Enum_savo)

		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Compile = {
		'ExternalEditor' : 'Errs',
	}

	def Compile(self, _object, _attributes={}, **_arguments):
		"""Compile: Compile the specified file(s)
		Required argument: List of files to compile
		Keyword argument ExternalEditor: Should the contents of the message window be returned to the caller?
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Errors for each file compiled
		"""
		_code = 'MMPR'
		_subcode = 'Comp'

		aetools.keysubst(_arguments, self._argmap_Compile)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Create_Project = {
		'from_stationery' : 'Tmpl',
	}

	def Create_Project(self, _object, _attributes={}, **_arguments):
		"""Create Project: Create a new project file
		Required argument: New project file specifier
		Keyword argument from_stationery: undocumented, typecode 'alis'
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'NewP'

		aetools.keysubst(_arguments, self._argmap_Create_Project)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Get_Definition(self, _object, _attributes={}, **_arguments):
		"""Get Definition: Returns the location(s) of a globally scoped function or data object.
		Required argument: undocumented, typecode 'TEXT'
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: undocumented, typecode 'FDef'
		"""
		_code = 'MMPR'
		_subcode = 'GDef'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Get_Open_Documents(self, _no_object=None, _attributes={}, **_arguments):
		"""Get Open Documents: Returns the list of open documents
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: The list of documents
		"""
		_code = 'MMPR'
		_subcode = 'GDoc'

		if _arguments: raise TypeError, 'No optional args expected'
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Get_Preferences = {
		'of' : 'PRec',
		'from_panel' : 'PNam',
	}

	def Get_Preferences(self, _no_object=None, _attributes={}, **_arguments):
		"""Get Preferences: Get the preferences for the current project
		Keyword argument of: Names of requested preferences
		Keyword argument from_panel: Name of the preference panel
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: The requested preferences
		"""
		_code = 'MMPR'
		_subcode = 'Gref'

		aetools.keysubst(_arguments, self._argmap_Get_Preferences)
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Get_Project_File = {
		'Segment' : 'Segm',
	}

	def Get_Project_File(self, _object, _attributes={}, **_arguments):
		"""Get Project File: Returns a description of a file in the project window.
		Required argument: The index of the file within its segment.
		Keyword argument Segment: The segment containing the file.
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: undocumented, typecode 'SrcF'
		"""
		_code = 'MMPR'
		_subcode = 'GFil'

		aetools.keysubst(_arguments, self._argmap_Get_Project_File)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Get_Project_Specifier(self, _no_object=None, _attributes={}, **_arguments):
		"""Get Project Specifier: Return the File Specifier for the current project
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: File Specifier for the current project
		"""
		_code = 'MMPR'
		_subcode = 'GetP'

		if _arguments: raise TypeError, 'No optional args expected'
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Get_Segments(self, _no_object=None, _attributes={}, **_arguments):
		"""Get Segments: Returns a description of each segment in the project.
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: undocumented, typecode 'Seg '
		"""
		_code = 'MMPR'
		_subcode = 'GSeg'

		if _arguments: raise TypeError, 'No optional args expected'
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Get_member_function_names(self, _object, _attributes={}, **_arguments):
		"""Get member function names: Returns a list containing the names of all the member functions of a class object
		Required argument: must be a class object
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: undocumented, typecode 'list'
		"""
		_code = 'MMPR'
		_subcode = 'MbFN'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Get_nonsimple_classes(self, _no_object=None, _attributes={}, **_arguments):
		"""Get nonsimple classes: Returns an alphabetical list of classes with member functions, bases classes, or subclasses
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: undocumented, typecode 'list'
		"""
		_code = 'MMPR'
		_subcode = 'NsCl'

		if _arguments: raise TypeError, 'No optional args expected'
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Goto_Function(self, _object, _attributes={}, **_arguments):
		"""Goto Function: Goto Specified Function Name
		Required argument: undocumented, typecode 'TEXT'
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'GoFn'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Goto_Line(self, _object, _attributes={}, **_arguments):
		"""Goto Line: Goto Specified Line Number
		Required argument: The requested source file line number
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'GoLn'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Is_In_Project(self, _object, _attributes={}, **_arguments):
		"""Is In Project: Whether or not the specified file(s) is in the current project
		Required argument: List of files to check for project membership
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Result code for each file
		"""
		_code = 'MMPR'
		_subcode = 'FInP'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Make_Project = {
		'ExternalEditor' : 'Errs',
	}

	def Make_Project(self, _no_object=None, _attributes={}, **_arguments):
		"""Make Project: Make the current project
		Keyword argument ExternalEditor: Should the contents of the message window be returned to the caller?
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Errors that occurred while making the project
		"""
		_code = 'MMPR'
		_subcode = 'Make'

		aetools.keysubst(_arguments, self._argmap_Make_Project)
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Open_browser(self, _object, _attributes={}, **_arguments):
		"""Open browser: Display a class, member function, or data member object in a single class browser window
		Required argument: an AE object reference
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'Brow'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Precompile = {
		'Saving_As' : 'Targ',
		'ExternalEditor' : 'Errs',
	}

	def Precompile(self, _object, _attributes={}, **_arguments):
		"""Precompile: Precompile the specified file to the specified destination file
		Required argument: File to precompile
		Keyword argument Saving_As: Destination file for precompiled header
		Keyword argument ExternalEditor: Should the contents of the message window be returned to the caller?
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Errors for the precompiled file
		"""
		_code = 'MMPR'
		_subcode = 'PreC'

		aetools.keysubst(_arguments, self._argmap_Precompile)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Preprocess = {
		'ExternalEditor' : 'Errs',
	}

	def Preprocess(self, _object, _attributes={}, **_arguments):
		"""Preprocess: Preprocesses the specified file(s)
		Required argument: undocumented, typecode 'alis'
		Keyword argument ExternalEditor: undocumented, typecode 'bool'
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Errors for each preprocessed file
		"""
		_code = 'MMPR'
		_subcode = 'PreP'

		aetools.keysubst(_arguments, self._argmap_Preprocess)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Remove_Binaries(self, _no_object=None, _attributes={}, **_arguments):
		"""Remove Binaries: Remove the binary object code from the current project
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'RemB'

		if _arguments: raise TypeError, 'No optional args expected'
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Remove_Files(self, _object, _attributes={}, **_arguments):
		"""Remove Files: Remove the specified file(s) from the current project
		Required argument: List of files to remove
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Error code for each file removed
		"""
		_code = 'MMPR'
		_subcode = 'RemF'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Reset_File_Paths(self, _no_object=None, _attributes={}, **_arguments):
		"""Reset File Paths: Resets access paths for all files belonging to open project.
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'ReFP'

		if _arguments: raise TypeError, 'No optional args expected'
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Run_Project = {
		'ExternalEditor' : 'Errs',
		'SourceDebugger' : 'DeBg',
	}

	def Run_Project(self, _no_object=None, _attributes={}, **_arguments):
		"""Run Project: Run the current project
		Keyword argument ExternalEditor: Should the contents of the message window be returned to the caller?
		Keyword argument SourceDebugger: Run the application under the control of the source-level debugger
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Errors that occurred when running the project
		"""
		_code = 'MMPR'
		_subcode = 'RunP'

		aetools.keysubst(_arguments, self._argmap_Run_Project)
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Save_Error_Window_As(self, _object, _attributes={}, **_arguments):
		"""Save Error Window As: Saves the Errors & Warnings window as a text file
		Required argument: Destination file for Save Message Window As
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'SvMs'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Set_Current_Target(self, _object=None, _attributes={}, **_arguments):
		"""Set Current Target: Set the current target of a project
		Required argument: Name of target
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'STrg'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Set_Default_Project(self, _object, _attributes={}, **_arguments):
		"""Set Default Project: Set the default project
		Required argument: Name of project
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'SDfP'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Set_Modification_Date = {
		'to' : 'MDat',
	}

	def Set_Modification_Date(self, _object, _attributes={}, **_arguments):
		"""Set Modification Date: Changes the internal modification date of the specified file(s)
		Required argument: List of files
		Keyword argument to: undocumented, typecode 'ldt '
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Error code for each modified file
		"""
		_code = 'MMPR'
		_subcode = 'SMod'

		aetools.keysubst(_arguments, self._argmap_Set_Modification_Date)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Set_Preferences = {
		'of_panel' : 'PNam',
		'to' : 'PRec',
	}

	def Set_Preferences(self, _no_object=None, _attributes={}, **_arguments):
		"""Set Preferences: Set the preferences for the current project
		Keyword argument of_panel: Name of the preference panel
		Keyword argument to: Preferences settings
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'Pref'

		aetools.keysubst(_arguments, self._argmap_Set_Preferences)
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Set_Project_File = {
		'to' : 'SrcS',
	}

	def Set_Project_File(self, _object, _attributes={}, **_arguments):
		"""Set Project File: Changes the settings for a given file in the project.
		Required argument: The name of the file
		Keyword argument to: The new settings for the file
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'SFil'

		aetools.keysubst(_arguments, self._argmap_Set_Project_File)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Set_Segment = {
		'to' : 'Segm',
	}

	def Set_Segment(self, _object, _attributes={}, **_arguments):
		"""Set Segment: Changes the name and attributes of a segment.
		Required argument: The segment to change
		Keyword argument to: The new name and attributes for the segment.
		Keyword argument _attributes: AppleEvent attribute dictionary
		"""
		_code = 'MMPR'
		_subcode = 'SSeg'

		aetools.keysubst(_arguments, self._argmap_Set_Segment)
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	def Touch(self, _object, _attributes={}, **_arguments):
		"""Touch: Force recompilation of the specified file(s)
		Required argument: List of files to compile
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Error code for each file touched
		"""
		_code = 'MMPR'
		_subcode = 'Toch'

		if _arguments: raise TypeError, 'No optional args expected'
		_arguments['----'] = _object


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']

	_argmap_Update_Project = {
		'ExternalEditor' : 'Errs',
	}

	def Update_Project(self, _no_object=None, _attributes={}, **_arguments):
		"""Update Project: Update the current project
		Keyword argument ExternalEditor: Should the contents of the message window be returned to the caller?
		Keyword argument _attributes: AppleEvent attribute dictionary
		Returns: Errors that occurred while updating the project
		"""
		_code = 'MMPR'
		_subcode = 'UpdP'

		aetools.keysubst(_arguments, self._argmap_Update_Project)
		if _no_object != None: raise TypeError, 'No direct arg expected'


		_reply, _arguments, _attributes = self.send(_code, _subcode,
				_arguments, _attributes)
		if _arguments.get('errn', 0):
			raise aetools.Error, aetools.decodeerror(_arguments)
		# XXXX Optionally decode result
		if _arguments.has_key('----'):
			return _arguments['----']


class Browser_Coloring(aetools.ComponentItem):
	"""Browser Coloring - Colors for Browser symbols. """
	want = 'BRKW'
class Browser_Keywords(aetools.NProperty):
	"""Browser Keywords - Mark Browser symbols with color. """
	which = 'BW00'
	want = 'bool'
class Classes_Color(aetools.NProperty):
	"""Classes Color - The color for classes. """
	which = 'BW01'
	want = 'cRGB'
class Constants_Color(aetools.NProperty):
	"""Constants Color - The color for constants. """
	which = 'BW02'
	want = 'cRGB'
class Enums_Color(aetools.NProperty):
	"""Enums Color - The color for enums. """
	which = 'BW03'
	want = 'cRGB'
class Functions_Color(aetools.NProperty):
	"""Functions Color - Set color for functions. """
	which = 'BW04'
	want = 'cRGB'
class Globals_Color(aetools.NProperty):
	"""Globals Color - The color for globals """
	which = 'BW05'
	want = 'cRGB'
class Macros_Color(aetools.NProperty):
	"""Macros Color - The color for macros. """
	which = 'BW06'
	want = 'cRGB'
class Template_Commands_in_Menu(aetools.NProperty):
	"""Template Commands in Menu - Include template commands in context menus """
	which = 'BW10'
	want = 'bool'
class Templates_Color(aetools.NProperty):
	"""Templates Color - Set color for templates. """
	which = 'BW07'
	want = 'cRGB'
class Typedefs_Color(aetools.NProperty):
	"""Typedefs Color - The color for typedefs. """
	which = 'BW08'
	want = 'cRGB'

class Build_Settings(aetools.ComponentItem):
	"""Build Settings - Build Settings preferences. """
	want = 'BSTG'
class Build_Before_Running(aetools.NProperty):
	"""Build Before Running - Build the target before running. """
	which = 'BX04'
	want = 'BXbr'
class Compiler_Thread_Stack_Size(aetools.NProperty):
	"""Compiler Thread Stack Size - Compiler Thread Stack Size """
	which = 'BX06'
	want = 'long'
class Completion_Sound(aetools.NProperty):
	"""Completion Sound - Play a sound when finished a Bring Up To Date or Make command. """
	which = 'BX01'
	want = 'bool'
class Failure_Sound(aetools.NProperty):
	"""Failure Sound - The sound CodeWarrior plays when it cannot finish a Bring Up To Date or Make command. """
	which = 'BX03'
	want = 'TEXT'
class Include_Cache_Size(aetools.NProperty):
	"""Include Cache Size - Include file cache size. """
	which = 'BX05'
	want = 'long'
class Save_Before_Building(aetools.NProperty):
	"""Save Before Building - Save open editor files before build operations """
	which = 'BX07'
	want = 'bool'
class Success_Sound(aetools.NProperty):
	"""Success Sound - The sound CodeWarrior plays when it successfully finishes a Bring Up To Date or Make command. """
	which = 'BX02'
	want = 'TEXT'

class base_class(aetools.ComponentItem):
	"""base class - A base class or super class of a class """
	want = 'BsCl'
class access(aetools.NProperty):
	"""access -  """
	which = 'Acce'
	want = 'Acce'
class class_(aetools.NProperty):
	"""class - The class object corresponding to this base class """
	which = 'Clas'
	want = 'obj '
class virtual(aetools.NProperty):
	"""virtual -  """
	which = 'Virt'
	want = 'bool'

base_classes = base_class

class Custom_Keywords(aetools.ComponentItem):
	"""Custom Keywords -  """
	want = 'CUKW'
class Custom_Color_1(aetools.NProperty):
	"""Custom Color 1 - The color for the first set of custom keywords. """
	which = 'GH05'
	want = 'cRGB'
class Custom_Color_2(aetools.NProperty):
	"""Custom Color 2 - The color for the second set custom keywords. """
	which = 'GH06'
	want = 'cRGB'
class Custom_Color_3(aetools.NProperty):
	"""Custom Color 3 - The color for the third set of custom keywords. """
	which = 'GH07'
	want = 'cRGB'
class Custom_Color_4(aetools.NProperty):
	"""Custom Color 4 - The color for the fourth set of custom keywords. """
	which = 'GH08'
	want = 'cRGB'

class browser_catalog(aetools.ComponentItem):
	"""browser catalog - The browser symbol catalog for the current project """
	want = 'Cata'
#        element 'Clas' as ['indx', 'name']

class class_(aetools.ComponentItem):
	"""class - A class, struct, or record type in the current project. """
	want = 'Clas'
class all_subclasses(aetools.NProperty):
	"""all subclasses - the classes directly or indirectly derived from this class """
	which = 'SubA'
	want = 'Clas'
class declaration_end_offset(aetools.NProperty):
	"""declaration end offset - End of class declaration """
	which = 'DcEn'
	want = 'long'
class declaration_file(aetools.NProperty):
	"""declaration file - Source file containing the class declaration """
	which = 'DcFl'
	want = 'fss '
class declaration_start_offset(aetools.NProperty):
	"""declaration start offset - Start of class declaration source code """
	which = 'DcSt'
	want = 'long'
class language(aetools.NProperty):
	"""language - Implementation language of this class """
	which = 'Lang'
	want = 'Lang'
class name(aetools.NProperty):
	"""name -  """
	which = 'pnam'
	want = 'TEXT'
class subclasses(aetools.NProperty):
	"""subclasses - the immediate subclasses of this class """
	which = 'SubC'
	want = 'Clas'
#        element 'BsCl' as ['indx']
#        element 'DtMb' as ['indx', 'name']
#        element 'MbFn' as ['indx', 'name']

classes = class_

class Debugger_Display(aetools.ComponentItem):
	"""Debugger Display - Debugger Display preferences """
	want = 'DbDS'
class Default_Array_Size(aetools.NProperty):
	"""Default Array Size - Controls whether CodeWarrior uses its own integrated editor or an external application for editing text files. """
	which = 'Db08'
	want = 'shor'
class Show_As_Decimal(aetools.NProperty):
	"""Show As Decimal - Show variable values as decimal by default """
	which = 'Db10'
	want = 'bool'
class Show_Locals(aetools.NProperty):
	"""Show Locals - Show locals by default """
	which = 'Db09'
	want = 'bool'
class Show_Variable_Types(aetools.NProperty):
	"""Show Variable Types - Show variable types by default. """
	which = 'Db01'
	want = 'bool'
class Sort_By_Method(aetools.NProperty):
	"""Sort By Method - Sort functions by method. """
	which = 'Db02'
	want = 'bool'
class Threads_in_Window(aetools.NProperty):
	"""Threads in Window - Show threads in separate windows. """
	which = 'Db04'
	want = 'bool'
class Use_RTTI(aetools.NProperty):
	"""Use RTTI - Enable RunTime Type Information. """
	which = 'Db03'
	want = 'bool'
class Variable_Changed_Hilite(aetools.NProperty):
	"""Variable Changed Hilite - Variable changed hilite color. """
	which = 'Db07'
	want = 'cRGB'
class Variable_Hints(aetools.NProperty):
	"""Variable Hints - Show variable hints. """
	which = 'Db05'
	want = 'bool'
class Watchpoint_Hilite(aetools.NProperty):
	"""Watchpoint Hilite - Watchpoint hilite color. """
	which = 'Db06'
	want = 'cRGB'

class Debugger_Global(aetools.ComponentItem):
	"""Debugger Global - Debugger Global preferences """
	want = 'DbGL'
class Auto_Target_Libraries(aetools.NProperty):
	"""Auto Target Libraries - Automatically target libraries when debugging """
	which = 'Dg11'
	want = 'bool'
class Cache_Edited_Files(aetools.NProperty):
	"""Cache Edited Files - Cache edit files between debug sessions """
	which = 'Dg12'
	want = 'bool'
class Confirm_Kill(aetools.NProperty):
	"""Confirm Kill - Confirm the \xd4killing\xd5 of the process. """
	which = 'Dg04'
	want = 'bool'
class Dont_Step_in_Runtime(aetools.NProperty):
	"""Dont Step in Runtime - Don\xd5t step into runtime code when debugging. """
	which = 'Dg07'
	want = 'bool'
class File_Cache_Duration(aetools.NProperty):
	"""File Cache Duration - Duration to keep files in cache (in days) """
	which = 'Dg13'
	want = 'shor'
class Ignore_Mod_Dates(aetools.NProperty):
	"""Ignore Mod Dates - Ignore modification dates of files. """
	which = 'Dg01'
	want = 'bool'
class Launch_Apps_on_Open(aetools.NProperty):
	"""Launch Apps on Open - Launch applications on the opening of sym files. """
	which = 'Dg03'
	want = 'bool'
class Open_All_Classes(aetools.NProperty):
	"""Open All Classes - Open all Java class files. """
	which = 'Dg02'
	want = 'bool'
class Select_Stack_Crawl(aetools.NProperty):
	"""Select Stack Crawl - Select the stack crawl. """
	which = 'Dg06'
	want = 'bool'
class Stop_at_Main(aetools.NProperty):
	"""Stop at Main - Stop to debug on the main() function. """
	which = 'Dg05'
	want = 'bool'

class Debugger_Target(aetools.ComponentItem):
	"""Debugger Target - Debugger Target preferences """
	want = 'DbTG'
class Cache_symbolics(aetools.NProperty):
	"""Cache symbolics - Cache symbolics between runs when executable doesn\xd5t change, else release symbolics files after killing process. """
	which = 'Dt15'
	want = 'bool'
class Data_Update_Interval(aetools.NProperty):
	"""Data Update Interval - How often to update the data while running (in seconds) """
	which = 'Dt09'
	want = 'long'
class Log_System_Messages(aetools.NProperty):
	"""Log System Messages - Log all system messages while debugging. """
	which = 'Dt02'
	want = 'bool'
class Relocated_Executable_Path(aetools.NProperty):
	"""Relocated Executable Path - Path to location of relocated libraries, code resources or remote debugging folder """
	which = 'Dt10'
	want = 'RlPt'
class Stop_at_temp_breakpoint(aetools.NProperty):
	"""Stop at temp breakpoint - Stop at a temp breakpoint on program launch. Set breakpoint type in Temp Breakpoint Type AppleEvent. """
	which = 'Dt13'
	want = 'bool'
class Temp_Breakpoint_Type(aetools.NProperty):
	"""Temp Breakpoint Type - Type of temp breakpoint to set on program launch. """
	which = 'Dt16'
	want = 'TmpB'
class Temp_breakpoint_names(aetools.NProperty):
	"""Temp breakpoint names - Comma separated list of names to attempt to stop at on program launch. First symbol to resolve in list is the temp BP that will be set. """
	which = 'Dt14'
	want = 'ctxt'
class Update_Data_While_Running(aetools.NProperty):
	"""Update Data While Running - Should pause to update data while running """
	which = 'Dt08'
	want = 'bool'

class Debugger_Windowing(aetools.ComponentItem):
	"""Debugger Windowing -  """
	want = 'DbWN'
class Debugging_Start_Action(aetools.NProperty):
	"""Debugging Start Action - What action to take when debug session starts """
	which = 'Dw01'
	want = 'DbSA'
class Do_Nothing_To_Projects(aetools.NProperty):
	"""Do Nothing To Projects - Suppress debugging start action for project windows """
	which = 'Dw02'
	want = 'bool'

class data_member(aetools.ComponentItem):
	"""data member - A class data member or field """
	want = 'DtMb'
class static(aetools.NProperty):
	"""static -  """
	which = 'Stat'
	want = 'bool'

data_members = data_member

class Editor(aetools.ComponentItem):
	"""Editor -  """
	want = 'EDTR'
class Background_Color(aetools.NProperty):
	"""Background Color - Color of the background of editor windows. """
	which = 'ED13'
	want = 'cRGB'
class Balance(aetools.NProperty):
	"""Balance - Flash the matching opening bracket when you type a closing bracket. """
	which = 'ED03'
	want = 'bool'
class Context_Popup_Delay(aetools.NProperty):
	"""Context Popup Delay - The amount of time, in sixtieths of a second, before the context popup is displayed if you click and hold on a browser symbol. """
	which = 'ED14'
	want = 'long'
class Default_Text_File_Format(aetools.NProperty):
	"""Default Text File Format - Default text file format (i.e. which type of line endings to use) """
	which = 'ED17'
	want = 'TxtF'
class Dynamic_Scroll(aetools.NProperty):
	"""Dynamic Scroll - Display a window\xd5s contents as you move the scroll box. """
	which = 'ED02'
	want = 'bool'
class Flash_Delay(aetools.NProperty):
	"""Flash Delay - The amount of time, in sixtieths of a second, the editor highlights a matching bracket. """
	which = 'ED01'
	want = 'long'
class Left_Margin_Line_Select(aetools.NProperty):
	"""Left Margin Line Select - Clicking in the left margin selects lines """
	which = 'ED16'
	want = 'bool'
class Main_Text_Color(aetools.NProperty):
	"""Main Text Color - Main, default, color for text. """
	which = 'ED12'
	want = 'cRGB'
class Relaxed_C_Popup_Parsing(aetools.NProperty):
	"""Relaxed C Popup Parsing - Relax the function parser for C source files """
	which = 'ED15'
	want = 'bool'
class Remember_Font(aetools.NProperty):
	"""Remember Font - Display a source file with its own font settings. """
	which = 'ED08'
	want = 'bool'
class Remember_Selection(aetools.NProperty):
	"""Remember Selection - Restore the previous selection in a file when you open it. """
	which = 'ED09'
	want = 'bool'
class Remember_Window(aetools.NProperty):
	"""Remember Window - Restore the last size and position for a source file window when you open it. """
	which = 'ED10'
	want = 'bool'
class Sort_Function_Popup(aetools.NProperty):
	"""Sort Function Popup -  """
	which = 'ED06'
	want = 'bool'
class Use_Drag__26__Drop_Editing(aetools.NProperty):
	"""Use Drag & Drop Editing - Use Drag & Drop text editing. """
	which = 'ED04'
	want = 'bool'
class Use_Multiple_Undo(aetools.NProperty):
	"""Use Multiple Undo -  """
	which = 'ED07'
	want = 'bool'

class Environment_Variable(aetools.ComponentItem):
	"""Environment Variable - Environment variable for host OS """
	want = 'EnvV'
class value(aetools.NProperty):
	"""value - Value of the environment variable """
	which = 'Valu'
	want = 'TEXT'

class Error_Information(aetools.ComponentItem):
	"""Error Information - Describes a single error or warning from the compiler or the linker. """
	want = 'ErrM'
class disk_file(aetools.NProperty):
	"""disk file - The file where the error occurred.  May not be returned for certain kinds of errors (eg, link errors). """
	which = 'file'
	want = 'fss '
class lineNumber(aetools.NProperty):
	"""lineNumber - The line in the file where the error occurred.  May not be returned for certain kinds of errors (eg, link errors). """
	which = 'ErrL'
	want = 'long'
class message(aetools.NProperty):
	"""message - The error or warning message. """
	which = 'ErrS'
	want = 'TEXT'
class messageKind(aetools.NProperty):
	"""messageKind - The type of error or warning. """
	which = 'ErrT'
	want = 'ErrT'

class Function_Information(aetools.ComponentItem):
	"""Function Information - Describes the location of any function or global data definition within the current project. """
	want = 'FDef'

class File_Mappings(aetools.ComponentItem):
	"""File Mappings - Mappings of extensions & file types to compilers """
	want = 'FLMP'
class Mappings(aetools.NProperty):
	"""Mappings -  """
	which = 'FMps'
	want = 'FMap'

class File_Mapping(aetools.ComponentItem):
	"""File Mapping -  """
	want = 'FMap'
class Compiler(aetools.NProperty):
	"""Compiler -  """
	which = 'TA07'
	want = 'TEXT'
class Extension(aetools.NProperty):
	"""Extension -  """
	which = 'TA02'
	want = 'TEXT'
class File_Type(aetools.NProperty):
	"""File Type -  """
	which = 'PR04'
	want = 'TEXT'
class Ignored_by_Make(aetools.NProperty):
	"""Ignored by Make -  """
	which = 'TA06'
	want = 'bool'
class Launchable(aetools.NProperty):
	"""Launchable -  """
	which = 'TA05'
	want = 'bool'
class Precompiled(aetools.NProperty):
	"""Precompiled -  """
	which = 'TA03'
	want = 'bool'
class Resource_File(aetools.NProperty):
	"""Resource File -  """
	which = 'TA04'
	want = 'bool'

class Global_Source_Trees(aetools.ComponentItem):
	"""Global Source Trees - Globally-defined source tree roots """
	want = 'GSTs'
class Source_Trees(aetools.NProperty):
	"""Source Trees - List of source tree roots """
	which = 'ST01'
	want = 'SrcT'

class Extras(aetools.ComponentItem):
	"""Extras -  """
	want = 'GXTR'
class Automatic_Toolbar_Help(aetools.NProperty):
	"""Automatic Toolbar Help - Automatically show balloon help in toolbar after delay """
	which = 'EX19'
	want = 'bool'
class External_Reference(aetools.NProperty):
	"""External Reference - Which on-line function reference to use. """
	which = 'EX08'
	want = 'RefP'
class Full_Screen_Zoom(aetools.NProperty):
	"""Full Screen Zoom - Zoom windows to the full screen width. """
	which = 'EX07'
	want = 'bool'
class Recent_Editor_Count(aetools.NProperty):
	"""Recent Editor Count - Maximum number of editor documents to show in the \xd2Open Recent\xd3 menu """
	which = 'EX16'
	want = 'shor'
class Recent_Project_Count(aetools.NProperty):
	"""Recent Project Count - Maximum number of project documents to show in the \xd2Open Recent\xd3 menu """
	which = 'EX17'
	want = 'shor'
class Use_Editor_Extensions(aetools.NProperty):
	"""Use Editor Extensions - Controls the use of the Editor Extensions menu """
	which = 'EX10'
	want = 'bool'
class Use_External_Editor(aetools.NProperty):
	"""Use External Editor - Controls whether CodeWarrior uses its own integrated editor or an external application for editing text files. """
	which = 'EX11'
	want = 'bool'
class Use_Script_Menu(aetools.NProperty):
	"""Use Script Menu - Controls the use of the AppleScript menu """
	which = 'EX12'
	want = 'bool'
class Use_ToolServer_Menu(aetools.NProperty):
	"""Use ToolServer Menu - Controls the use of the ToolServer menu """
	which = 'EX18'
	want = 'bool'

class Build_Extras(aetools.ComponentItem):
	"""Build Extras -  """
	want = 'LXTR'
class Browser_Active(aetools.NProperty):
	"""Browser Active - Allow the collection of browser information. """
	which = 'EX09'
	want = 'bool'
class Cache_Subproject_Data(aetools.NProperty):
	"""Cache Subproject Data -  """
	which = 'EX31'
	want = 'bool'
class Dump_Browser_Info(aetools.NProperty):
	"""Dump Browser Info -  """
	which = 'EX30'
	want = 'bool'
class Modification_Date_Caching(aetools.NProperty):
	"""Modification Date Caching -  """
	which = 'EX04'
	want = 'bool'

class member_function(aetools.ComponentItem):
	"""member function - A class member function or method. """
	want = 'MbFn'
class implementation_end_offset(aetools.NProperty):
	"""implementation end offset - end of member function definition """
	which = 'DfEn'
	want = 'long'
class implementation_file(aetools.NProperty):
	"""implementation file - Source file containing the member function definition """
	which = 'DfFl'
	want = 'fss '
class implementation_start_offset(aetools.NProperty):
	"""implementation start offset - start of member function definition source code """
	which = 'DfSt'
	want = 'long'

member_functions = member_function

class Access_Paths(aetools.ComponentItem):
	"""Access Paths - Contains the definitions of a project\xd5s access (search) paths. """
	want = 'PATH'
class Always_Full_Search(aetools.NProperty):
	"""Always Full Search - To force the compiler to search for system includes like it searches for user includes. """
	which = 'PA02'
	want = 'bool'
class Convert_Paths(aetools.NProperty):
	"""Convert Paths - Enables conversion of DOS & Unix-style relative paths when searching for files. """
	which = 'PA04'
	want = 'bool'
class Require_Framework_Includes(aetools.NProperty):
	"""Require Framework Includes - Causes the IDE to only look in the framework access paths if a Mac OS X framework style include (i.e. <Carbon/Carbon.h> ) is used. """
	which = 'PA05'
	want = 'bool'
class System_Paths(aetools.NProperty):
	"""System Paths - To add an access path for the include files. (Not supported in Pascal) """
	which = 'PA03'
	want = 'PInf'
class User_Paths(aetools.NProperty):
	"""User Paths - To add an access path for the source files. """
	which = 'PA01'
	want = 'PInf'

class Path_Information(aetools.ComponentItem):
	"""Path Information - Contains all of the parameters that describe an access path. """
	want = 'PInf'
class format(aetools.NProperty):
	"""format - Format of the a """
	which = 'Frmt'
	want = 'PthF'
class framework(aetools.NProperty):
	"""framework - Is the path a Mac OS X framework style path?  (This flag is readable but not writeable from AppleScript.) """
	which = 'Frmw'
	want = 'bool'
class host_flags(aetools.NProperty):
	"""host flags - Bit fields enabling the access path for each host OS (1 = Mac OS, 2 = Windows) """
	which = 'HstF'
	want = 'long'
class origin(aetools.NProperty):
	"""origin -  """
	which = 'Orig'
	want = 'PPrm'
class recursive(aetools.NProperty):
	"""recursive - Will the path be searched recursively?  (Default is true) """
	which = 'Recu'
	want = 'bool'
class root(aetools.NProperty):
	"""root - Name of the root of the relative path. Pre-defined values are \xd2Absolute\xd3, \xd2Project\xd3, \xd2CodeWarrior\xd3, and  \xd2System\xd3. Anything else is a user-defined root. """
	which = 'Root'
	want = 'TEXT'

class Plugin_Settings(aetools.ComponentItem):
	"""Plugin Settings - Settings for plugin tools """
	want = 'PSTG'
class Disable_Third_Party_COM_Plugins(aetools.NProperty):
	"""Disable Third Party COM Plugins - Disable COM plugins from third parties """
	which = 'PX02'
	want = 'bool'
class Plugin_Diagnostics_Level(aetools.NProperty):
	"""Plugin Diagnostics Level - Plugin Diagnostics Level is for those who are developing plugins for the IDE and need to debug them. """
	which = 'PX01'
	want = 'PXdg'

class Runtime_Settings(aetools.ComponentItem):
	"""Runtime Settings - Runtime settings """
	want = 'RSTG'
class Command_Line_Arguments(aetools.NProperty):
	"""Command Line Arguments - Extra command line args to pass to executable """
	which = 'RS02'
	want = 'TEXT'
class Environment_Variables(aetools.NProperty):
	"""Environment Variables - Environment variables to use when running the executable """
	which = 'RS04'
	want = 'EnvV'
class Host_Application(aetools.NProperty):
	"""Host Application - Host application for running/debugging libraries and code resources """
	which = 'RS01'
	want = 'RlPt'
class Working_Directory(aetools.NProperty):
	"""Working Directory - Working directory to use when running the executable """
	which = 'RS03'
	want = 'TEXT'

class Relative_Path(aetools.ComponentItem):
	"""Relative Path - Relative path from some root """
	want = 'RlPt'

class Shielded_Folder(aetools.ComponentItem):
	"""Shielded Folder -  """
	want = 'SFit'
class Expression_To_Match(aetools.NProperty):
	"""Expression To Match - Regular expression which describes folders to skip """
	which = 'SF01'
	want = 'TEXT'
class Skip_Find_And_Compare_Operations(aetools.NProperty):
	"""Skip Find And Compare Operations - Matching folders will be skipped during find and compare operations """
	which = 'SF03'
	want = 'bool'
class Skip_Project_Operations(aetools.NProperty):
	"""Skip Project Operations - Matching folders will be skipped during project operations """
	which = 'SF02'
	want = 'bool'

class Shielded_Folders(aetools.ComponentItem):
	"""Shielded Folders - Folders skipped when performing project and find-and-compare operations """
	want = 'SHFL'
class Shielded_Items(aetools.NProperty):
	"""Shielded Items -  """
	which = 'SFis'
	want = 'SFit'

class Syntax_Coloring(aetools.ComponentItem):
	"""Syntax Coloring -  """
	want = 'SNTX'
class Comment_Color(aetools.NProperty):
	"""Comment Color - The color for comments. """
	which = 'GH02'
	want = 'cRGB'
class Keyword_Color(aetools.NProperty):
	"""Keyword Color - The color for language keywords. """
	which = 'GH03'
	want = 'cRGB'
class String_Color(aetools.NProperty):
	"""String Color - The color for strings. """
	which = 'GH04'
	want = 'cRGB'
class Syntax_Coloring(aetools.NProperty):
	"""Syntax Coloring - Mark keywords and comments with color. """
	which = 'GH01'
	want = 'bool'

class Segment(aetools.ComponentItem):
	"""Segment - A segment or group in the project """
	want = 'Seg '
class filecount(aetools.NProperty):
	"""filecount -  """
	which = 'NumF'
	want = 'shor'
class seg_2d_locked(aetools.NProperty):
	"""seg-locked - Is the segment locked ? [68K only] """
	which = 'PLck'
	want = 'bool'
class seg_2d_preloaded(aetools.NProperty):
	"""seg-preloaded - Is the segment preloaded ? [68K only] """
	which = 'Prel'
	want = 'bool'
class seg_2d_protected(aetools.NProperty):
	"""seg-protected - Is the segment protected ? [68K only] """
	which = 'Prot'
	want = 'bool'
class seg_2d_purgeable(aetools.NProperty):
	"""seg-purgeable - Is the segment purgeable ? [68K only] """
	which = 'Purg'
	want = 'bool'
class seg_2d_system_heap(aetools.NProperty):
	"""seg-system heap - Is the segment loaded into the system heap ? [68K only] """
	which = 'SysH'
	want = 'bool'

class ProjectFile(aetools.ComponentItem):
	"""ProjectFile - A file contained in a project """
	want = 'SrcF'
class codesize(aetools.NProperty):
	"""codesize - The size of this file\xd5s code. """
	which = 'CSiz'
	want = 'long'
class datasize(aetools.NProperty):
	"""datasize - The size of this file\xd5s data. """
	which = 'DSiz'
	want = 'long'
class filetype(aetools.NProperty):
	"""filetype - What kind of file is this ? """
	which = 'SrcT'
	want = 'SrcT'
class includes(aetools.NProperty):
	"""includes -  """
	which = 'IncF'
	want = 'fss '
class initialize_before(aetools.NProperty):
	"""initialize before - Initialize the shared library before the main application. """
	which = 'Bfor'
	want = 'bool'
class symbols(aetools.NProperty):
	"""symbols - Are debugging symbols generated for this file ? """
	which = 'SymG'
	want = 'bool'
class up_to_date(aetools.NProperty):
	"""up to date - Has the file been compiled since its last modification ? """
	which = 'UpTD'
	want = 'bool'
class weak_link(aetools.NProperty):
	"""weak link - Is this file imported weakly into the project ? [PowerPC only] """
	which = 'Weak'
	want = 'bool'

class Source_Tree(aetools.ComponentItem):
	"""Source Tree - User-defined source tree root """
	want = 'SrcT'
class path(aetools.NProperty):
	"""path - path for the user-defined source tree root """
	which = 'Path'
	want = 'TEXT'
class path_kind(aetools.NProperty):
	"""path kind - kind of path """
	which = 'Kind'
	want = 'STKd'

class Target_Settings(aetools.ComponentItem):
	"""Target Settings - Contains the definitions of a project\xd5s target. """
	want = 'TARG'
class Linker(aetools.NProperty):
	"""Linker - The name of the current linker. """
	which = 'TA01'
	want = 'TEXT'
class Output_Directory_Location(aetools.NProperty):
	"""Output Directory Location - Location of output directory """
	which = 'TA16'
	want = 'RlPt'
class Output_Directory_Origin(aetools.NProperty):
	"""Output Directory Origin - Origin of path to output directory. Usage of this property is deprecated. Use the \xd2Output Directory Location\xd3 property instead. """
	which = 'TA12'
	want = 'PPrm'
class Output_Directory_Path(aetools.NProperty):
	"""Output Directory Path - Path to output directory. Usage of this property is deprecated. Use the \xd2Output Directory Location\xd3 property instead. """
	which = 'TA11'
	want = 'TEXT'
class Post_Linker(aetools.NProperty):
	"""Post Linker -  """
	which = 'TA09'
	want = 'TEXT'
class Pre_Linker(aetools.NProperty):
	"""Pre Linker -  """
	which = 'TA13'
	want = 'TEXT'
class Target_Name(aetools.NProperty):
	"""Target Name -  """
	which = 'TA10'
	want = 'TEXT'
class Use_Relative_Paths(aetools.NProperty):
	"""Use Relative Paths - Save project entries using relative paths """
	which = 'TA15'
	want = 'bool'

class Target_Source_Trees(aetools.ComponentItem):
	"""Target Source Trees - Target-specific user-defined source tree roots """
	want = 'TSTs'

class VCS_Setup(aetools.ComponentItem):
	"""VCS Setup - The version control system preferences. """
	want = 'VCSs'
class Always_Prompt(aetools.NProperty):
	"""Always Prompt - Always show login dialog """
	which = 'VC07'
	want = 'bool'
class Auto_Connect(aetools.NProperty):
	"""Auto Connect - Automatically connect to database when starting. """
	which = 'VC05'
	want = 'bool'
class Connection_Method(aetools.NProperty):
	"""Connection Method - Name of Version Control System to use. """
	which = 'VC02'
	want = 'TEXT'
class Database_Path(aetools.NProperty):
	"""Database Path - Path to the VCS database. """
	which = 'VC09'
	want = 'RlPt'
class Local_Path(aetools.NProperty):
	"""Local Path - Path to the local root """
	which = 'VC10'
	want = 'RlPt'
class Mount_Volume(aetools.NProperty):
	"""Mount Volume - Attempt to mount the database volume if it isn't available. """
	which = 'VC08'
	want = 'bool'
class Password(aetools.NProperty):
	"""Password - The password for the VCS. """
	which = 'VC04'
	want = 'TEXT'
class Store_Password(aetools.NProperty):
	"""Store Password - Store the password. """
	which = 'VC06'
	want = 'bool'
class Use_Global_Settings(aetools.NProperty):
	"""Use Global Settings - Use the global VCS settings by default """
	which = 'VC11'
	want = 'bool'
class Username(aetools.NProperty):
	"""Username - The user name for the VCS. """
	which = 'VC03'
	want = 'TEXT'
class VCS_Active(aetools.NProperty):
	"""VCS Active - Use Version Control """
	which = 'VC01'
	want = 'bool'

class Font(aetools.ComponentItem):
	"""Font -  """
	want = 'mFNT'
class Auto_Indent(aetools.NProperty):
	"""Auto Indent - Indent new lines automatically. """
	which = 'FN01'
	want = 'bool'
class Tab_Indents_Selection(aetools.NProperty):
	"""Tab Indents Selection - Tab indents selection when multiple lines are selected """
	which = 'FN03'
	want = 'bool'
class Tab_Inserts_Spaces(aetools.NProperty):
	"""Tab Inserts Spaces - Insert spaces instead of tab character """
	which = 'FN04'
	want = 'bool'
class Tab_Size(aetools.NProperty):
	"""Tab Size -  """
	which = 'FN02'
	want = 'shor'
class Text_Font(aetools.NProperty):
	"""Text Font - The font used in editing windows. """
	which = 'ptxf'
	want = 'TEXT'
class Text_Size(aetools.NProperty):
	"""Text Size - The size of the text in an editing window. """
	which = 'ptps'
	want = 'shor'
Browser_Coloring._superclassnames = []
Browser_Coloring._privpropdict = {
	'Browser_Keywords' : Browser_Keywords,
	'Classes_Color' : Classes_Color,
	'Constants_Color' : Constants_Color,
	'Enums_Color' : Enums_Color,
	'Functions_Color' : Functions_Color,
	'Globals_Color' : Globals_Color,
	'Macros_Color' : Macros_Color,
	'Template_Commands_in_Menu' : Template_Commands_in_Menu,
	'Templates_Color' : Templates_Color,
	'Typedefs_Color' : Typedefs_Color,
}
Browser_Coloring._privelemdict = {
}
Build_Settings._superclassnames = []
Build_Settings._privpropdict = {
	'Build_Before_Running' : Build_Before_Running,
	'Compiler_Thread_Stack_Size' : Compiler_Thread_Stack_Size,
	'Completion_Sound' : Completion_Sound,
	'Failure_Sound' : Failure_Sound,
	'Include_Cache_Size' : Include_Cache_Size,
	'Save_Before_Building' : Save_Before_Building,
	'Success_Sound' : Success_Sound,
}
Build_Settings._privelemdict = {
}
base_class._superclassnames = []
base_class._privpropdict = {
	'access' : access,
	'class_' : class_,
	'virtual' : virtual,
}
base_class._privelemdict = {
}
Custom_Keywords._superclassnames = []
Custom_Keywords._privpropdict = {
	'Custom_Color_1' : Custom_Color_1,
	'Custom_Color_2' : Custom_Color_2,
	'Custom_Color_3' : Custom_Color_3,
	'Custom_Color_4' : Custom_Color_4,
}
Custom_Keywords._privelemdict = {
}
browser_catalog._superclassnames = []
browser_catalog._privpropdict = {
}
browser_catalog._privelemdict = {
	'class_' : class_,
}
class_._superclassnames = []
class_._privpropdict = {
	'all_subclasses' : all_subclasses,
	'declaration_end_offset' : declaration_end_offset,
	'declaration_file' : declaration_file,
	'declaration_start_offset' : declaration_start_offset,
	'language' : language,
	'name' : name,
	'subclasses' : subclasses,
}
class_._privelemdict = {
	'base_class' : base_class,
	'data_member' : data_member,
	'member_function' : member_function,
}
Debugger_Display._superclassnames = []
Debugger_Display._privpropdict = {
	'Default_Array_Size' : Default_Array_Size,
	'Show_As_Decimal' : Show_As_Decimal,
	'Show_Locals' : Show_Locals,
	'Show_Variable_Types' : Show_Variable_Types,
	'Sort_By_Method' : Sort_By_Method,
	'Threads_in_Window' : Threads_in_Window,
	'Use_RTTI' : Use_RTTI,
	'Variable_Changed_Hilite' : Variable_Changed_Hilite,
	'Variable_Hints' : Variable_Hints,
	'Watchpoint_Hilite' : Watchpoint_Hilite,
}
Debugger_Display._privelemdict = {
}
Debugger_Global._superclassnames = []
Debugger_Global._privpropdict = {
	'Auto_Target_Libraries' : Auto_Target_Libraries,
	'Cache_Edited_Files' : Cache_Edited_Files,
	'Confirm_Kill' : Confirm_Kill,
	'Dont_Step_in_Runtime' : Dont_Step_in_Runtime,
	'File_Cache_Duration' : File_Cache_Duration,
	'Ignore_Mod_Dates' : Ignore_Mod_Dates,
	'Launch_Apps_on_Open' : Launch_Apps_on_Open,
	'Open_All_Classes' : Open_All_Classes,
	'Select_Stack_Crawl' : Select_Stack_Crawl,
	'Stop_at_Main' : Stop_at_Main,
}
Debugger_Global._privelemdict = {
}
Debugger_Target._superclassnames = []
Debugger_Target._privpropdict = {
	'Auto_Target_Libraries' : Auto_Target_Libraries,
	'Cache_symbolics' : Cache_symbolics,
	'Data_Update_Interval' : Data_Update_Interval,
	'Log_System_Messages' : Log_System_Messages,
	'Relocated_Executable_Path' : Relocated_Executable_Path,
	'Stop_at_temp_breakpoint' : Stop_at_temp_breakpoint,
	'Temp_Breakpoint_Type' : Temp_Breakpoint_Type,
	'Temp_breakpoint_names' : Temp_breakpoint_names,
	'Update_Data_While_Running' : Update_Data_While_Running,
}
Debugger_Target._privelemdict = {
}
Debugger_Windowing._superclassnames = []
Debugger_Windowing._privpropdict = {
	'Debugging_Start_Action' : Debugging_Start_Action,
	'Do_Nothing_To_Projects' : Do_Nothing_To_Projects,
}
Debugger_Windowing._privelemdict = {
}
data_member._superclassnames = []
data_member._privpropdict = {
	'access' : access,
	'declaration_end_offset' : declaration_end_offset,
	'declaration_start_offset' : declaration_start_offset,
	'name' : name,
	'static' : static,
}
data_member._privelemdict = {
}
Editor._superclassnames = []
Editor._privpropdict = {
	'Background_Color' : Background_Color,
	'Balance' : Balance,
	'Context_Popup_Delay' : Context_Popup_Delay,
	'Default_Text_File_Format' : Default_Text_File_Format,
	'Dynamic_Scroll' : Dynamic_Scroll,
	'Flash_Delay' : Flash_Delay,
	'Left_Margin_Line_Select' : Left_Margin_Line_Select,
	'Main_Text_Color' : Main_Text_Color,
	'Relaxed_C_Popup_Parsing' : Relaxed_C_Popup_Parsing,
	'Remember_Font' : Remember_Font,
	'Remember_Selection' : Remember_Selection,
	'Remember_Window' : Remember_Window,
	'Sort_Function_Popup' : Sort_Function_Popup,
	'Use_Drag__26__Drop_Editing' : Use_Drag__26__Drop_Editing,
	'Use_Multiple_Undo' : Use_Multiple_Undo,
}
Editor._privelemdict = {
}
Environment_Variable._superclassnames = []
Environment_Variable._privpropdict = {
	'name' : name,
	'value' : value,
}
Environment_Variable._privelemdict = {
}
Error_Information._superclassnames = []
Error_Information._privpropdict = {
	'disk_file' : disk_file,
	'lineNumber' : lineNumber,
	'message' : message,
	'messageKind' : messageKind,
}
Error_Information._privelemdict = {
}
Function_Information._superclassnames = []
Function_Information._privpropdict = {
	'disk_file' : disk_file,
	'lineNumber' : lineNumber,
}
Function_Information._privelemdict = {
}
File_Mappings._superclassnames = []
File_Mappings._privpropdict = {
	'Mappings' : Mappings,
}
File_Mappings._privelemdict = {
}
File_Mapping._superclassnames = []
File_Mapping._privpropdict = {
	'Compiler' : Compiler,
	'Extension' : Extension,
	'File_Type' : File_Type,
	'Ignored_by_Make' : Ignored_by_Make,
	'Launchable' : Launchable,
	'Precompiled' : Precompiled,
	'Resource_File' : Resource_File,
}
File_Mapping._privelemdict = {
}
Global_Source_Trees._superclassnames = []
Global_Source_Trees._privpropdict = {
	'Source_Trees' : Source_Trees,
}
Global_Source_Trees._privelemdict = {
}
Extras._superclassnames = []
Extras._privpropdict = {
	'Automatic_Toolbar_Help' : Automatic_Toolbar_Help,
	'External_Reference' : External_Reference,
	'Full_Screen_Zoom' : Full_Screen_Zoom,
	'Recent_Editor_Count' : Recent_Editor_Count,
	'Recent_Project_Count' : Recent_Project_Count,
	'Use_Editor_Extensions' : Use_Editor_Extensions,
	'Use_External_Editor' : Use_External_Editor,
	'Use_Script_Menu' : Use_Script_Menu,
	'Use_ToolServer_Menu' : Use_ToolServer_Menu,
}
Extras._privelemdict = {
}
Build_Extras._superclassnames = []
Build_Extras._privpropdict = {
	'Browser_Active' : Browser_Active,
	'Cache_Subproject_Data' : Cache_Subproject_Data,
	'Dump_Browser_Info' : Dump_Browser_Info,
	'Modification_Date_Caching' : Modification_Date_Caching,
}
Build_Extras._privelemdict = {
}
member_function._superclassnames = []
member_function._privpropdict = {
	'access' : access,
	'declaration_end_offset' : declaration_end_offset,
	'declaration_file' : declaration_file,
	'declaration_start_offset' : declaration_start_offset,
	'implementation_end_offset' : implementation_end_offset,
	'implementation_file' : implementation_file,
	'implementation_start_offset' : implementation_start_offset,
	'name' : name,
	'static' : static,
	'virtual' : virtual,
}
member_function._privelemdict = {
}
Access_Paths._superclassnames = []
Access_Paths._privpropdict = {
	'Always_Full_Search' : Always_Full_Search,
	'Convert_Paths' : Convert_Paths,
	'Require_Framework_Includes' : Require_Framework_Includes,
	'System_Paths' : System_Paths,
	'User_Paths' : User_Paths,
}
Access_Paths._privelemdict = {
}
Path_Information._superclassnames = []
Path_Information._privpropdict = {
	'format' : format,
	'framework' : framework,
	'host_flags' : host_flags,
	'name' : name,
	'origin' : origin,
	'recursive' : recursive,
	'root' : root,
}
Path_Information._privelemdict = {
}
Plugin_Settings._superclassnames = []
Plugin_Settings._privpropdict = {
	'Disable_Third_Party_COM_Plugins' : Disable_Third_Party_COM_Plugins,
	'Plugin_Diagnostics_Level' : Plugin_Diagnostics_Level,
}
Plugin_Settings._privelemdict = {
}
Runtime_Settings._superclassnames = []
Runtime_Settings._privpropdict = {
	'Command_Line_Arguments' : Command_Line_Arguments,
	'Environment_Variables' : Environment_Variables,
	'Host_Application' : Host_Application,
	'Working_Directory' : Working_Directory,
}
Runtime_Settings._privelemdict = {
}
Relative_Path._superclassnames = []
Relative_Path._privpropdict = {
	'format' : format,
	'name' : name,
	'origin' : origin,
	'root' : root,
}
Relative_Path._privelemdict = {
}
Shielded_Folder._superclassnames = []
Shielded_Folder._privpropdict = {
	'Expression_To_Match' : Expression_To_Match,
	'Skip_Find_And_Compare_Operations' : Skip_Find_And_Compare_Operations,
	'Skip_Project_Operations' : Skip_Project_Operations,
}
Shielded_Folder._privelemdict = {
}
Shielded_Folders._superclassnames = []
Shielded_Folders._privpropdict = {
	'Shielded_Items' : Shielded_Items,
}
Shielded_Folders._privelemdict = {
}
Syntax_Coloring._superclassnames = []
Syntax_Coloring._privpropdict = {
	'Comment_Color' : Comment_Color,
	'Custom_Color_1' : Custom_Color_1,
	'Custom_Color_2' : Custom_Color_2,
	'Custom_Color_3' : Custom_Color_3,
	'Custom_Color_4' : Custom_Color_4,
	'Keyword_Color' : Keyword_Color,
	'String_Color' : String_Color,
	'Syntax_Coloring' : Syntax_Coloring,
}
Syntax_Coloring._privelemdict = {
}
Segment._superclassnames = []
Segment._privpropdict = {
	'filecount' : filecount,
	'name' : name,
	'seg_2d_locked' : seg_2d_locked,
	'seg_2d_preloaded' : seg_2d_preloaded,
	'seg_2d_protected' : seg_2d_protected,
	'seg_2d_purgeable' : seg_2d_purgeable,
	'seg_2d_system_heap' : seg_2d_system_heap,
}
Segment._privelemdict = {
}
ProjectFile._superclassnames = []
ProjectFile._privpropdict = {
	'codesize' : codesize,
	'datasize' : datasize,
	'disk_file' : disk_file,
	'filetype' : filetype,
	'includes' : includes,
	'initialize_before' : initialize_before,
	'name' : name,
	'symbols' : symbols,
	'up_to_date' : up_to_date,
	'weak_link' : weak_link,
}
ProjectFile._privelemdict = {
}
Source_Tree._superclassnames = []
Source_Tree._privpropdict = {
	'format' : format,
	'name' : name,
	'path' : path,
	'path_kind' : path_kind,
}
Source_Tree._privelemdict = {
}
Target_Settings._superclassnames = []
Target_Settings._privpropdict = {
	'Linker' : Linker,
	'Output_Directory_Location' : Output_Directory_Location,
	'Output_Directory_Origin' : Output_Directory_Origin,
	'Output_Directory_Path' : Output_Directory_Path,
	'Post_Linker' : Post_Linker,
	'Pre_Linker' : Pre_Linker,
	'Target_Name' : Target_Name,
	'Use_Relative_Paths' : Use_Relative_Paths,
}
Target_Settings._privelemdict = {
}
Target_Source_Trees._superclassnames = []
Target_Source_Trees._privpropdict = {
	'Source_Trees' : Source_Trees,
}
Target_Source_Trees._privelemdict = {
}
VCS_Setup._superclassnames = []
VCS_Setup._privpropdict = {
	'Always_Prompt' : Always_Prompt,
	'Auto_Connect' : Auto_Connect,
	'Connection_Method' : Connection_Method,
	'Database_Path' : Database_Path,
	'Local_Path' : Local_Path,
	'Mount_Volume' : Mount_Volume,
	'Password' : Password,
	'Store_Password' : Store_Password,
	'Use_Global_Settings' : Use_Global_Settings,
	'Username' : Username,
	'VCS_Active' : VCS_Active,
}
VCS_Setup._privelemdict = {
}
Font._superclassnames = []
Font._privpropdict = {
	'Auto_Indent' : Auto_Indent,
	'Tab_Indents_Selection' : Tab_Indents_Selection,
	'Tab_Inserts_Spaces' : Tab_Inserts_Spaces,
	'Tab_Size' : Tab_Size,
	'Text_Font' : Text_Font,
	'Text_Size' : Text_Size,
}
Font._privelemdict = {
}
_Enum_Acce = {
	'public' : 'Publ',	# 
	'protected' : 'Prot',	# 
	'private' : 'Priv',	# 
}

_Enum_BXbr = {
	'Always_Build' : 'BXb1',	# Always build the target before running.
	'Ask_Build' : 'BXb2',	# Ask before building the target when running.
	'Never_Build' : 'BXb3',	# Never before building the target before running.
}

_Enum_DbSA = {
	'No_Action' : 'DSA1',	# Don\xd5t do anything to non-debug windows
	'Hide_Windows' : 'DSA2',	# Hide non-debugging windows
	'Collapse_Windows' : 'DSA3',	# Collapse non-debugging windows
	'Close_Windows' : 'DSA4',	# Close non-debugging windows
}

_Enum_DgBL = {
	'Always' : 'DgB0',	# Always build before debugging.
	'Never' : 'DgB1',	# Never build before debugging.
	'Ask' : 'DgB2',	# Ask about building before debugging.
}

_Enum_ErrT = {
	'information' : 'ErIn',	# 
	'compiler_warning' : 'ErCW',	# 
	'compiler_error' : 'ErCE',	# 
	'definition' : 'ErDf',	# 
	'linker_warning' : 'ErLW',	# 
	'linker_error' : 'ErLE',	# 
	'find_result' : 'ErFn',	# 
	'generic_error' : 'ErGn',	# 
}

_Enum_Inte = {
	'never_interact' : 'eNvr',	# Never allow user interactions
	'interact_with_self' : 'eInS',	# Allow user interaction only when an AppleEvent is sent from within CodeWarrior
	'interact_with_local' : 'eInL',	# Allow user interaction when AppleEvents are sent from applications on the same machine (default)
	'interact_with_all' : 'eInA',	# Allow user interaction from both local and remote AppleEvents
}

_Enum_Lang = {
	'C' : 'LC  ',	# 
	'C_2b__2b_' : 'LC++',	# 
	'Pascal' : 'LP  ',	# 
	'Object_Pascal' : 'LP++',	# 
	'Java' : 'LJav',	# 
	'Assembler' : 'LAsm',	# 
	'Unknown' : 'L?  ',	# 
}

_Enum_PPrm = {
	'absolute' : 'Abso',	# An absolute path name, including volume name.
	'project_relative' : 'PRel',	# A path relative to the current project\xd5s folder.
	'shell_relative' : 'SRel',	# A path relative to the CodeWarrior\xaa folder.
	'system_relative' : 'YRel',	# A path relative to the system folder
	'root_relative' : 'RRel',	# 
}

_Enum_PXdg = {
	'Diagnose_None' : 'PXd1',	# No Plugin Diagnostics.
	'Diagnose_Errors' : 'PXd2',	# Plugin Diagnostics for errors only.
	'Diagnose_All' : 'PXd3',	# Plugin Diagnostics for everything.
}

_Enum_PthF = {
	'Generic_Path' : 'PFGn',	# 
	'MacOS_Path' : 'PFMc',	# MacOS path using colon as separator
	'Windows_Path' : 'PFWn',	# Windows path using backslash as separator
	'Unix_Path' : 'PFUx',	# Unix path using slash as separator
}

_Enum_RefP = {
	'Think_Reference' : 'DanR',	# 
	'QuickView' : 'ALTV',	# 
}

_Enum_STKd = {
	'Absolute_Path' : 'STK0',	# The \xd2path\xd3 property is an absolute path to the location of the source tree.
	'Registry_Key' : 'STK1',	# The \xd2path\xd3 property is the name of a registry key that contains the path to the root.
	'Environment_Variable' : 'STK2',	# The \xd2path\xd3 property is the name of an environment variable that contains the path to the root.
}

_Enum_SrcT = {
	'source' : 'FTxt',	# A source file (.c, .cp, .p, etc).
	'unknown' : 'FUnk',	# An unknown file type.
}

_Enum_TmpB = {
	'User_Specified' : 'Usrs',	# Use user specified symbols when setting temporary breakpoints on program launch.
	'Default' : 'Dflt',	# Use system default symbols when setting temporary breakpoints on program launch.
}

_Enum_TxtF = {
	'MacOS' : 'TxF0',	# MacOS text format
	'DOS' : 'TxF1',	# DOS text format
	'Unix' : 'TxF2',	# Unix text format
}

_Enum_savo = {
	'yes' : 'yes ',	# Save changes
	'no' : 'no  ',	# Do not save changes
	'ask' : 'ask ',	# Ask the user whether to save
}


#
# Indices of types declared in this module
#
_classdeclarations = {
	'BRKW' : Browser_Coloring,
	'BSTG' : Build_Settings,
	'BsCl' : base_class,
	'CUKW' : Custom_Keywords,
	'Cata' : browser_catalog,
	'Clas' : class_,
	'DbDS' : Debugger_Display,
	'DbGL' : Debugger_Global,
	'DbTG' : Debugger_Target,
	'DbWN' : Debugger_Windowing,
	'DtMb' : data_member,
	'EDTR' : Editor,
	'EnvV' : Environment_Variable,
	'ErrM' : Error_Information,
	'FDef' : Function_Information,
	'FLMP' : File_Mappings,
	'FMap' : File_Mapping,
	'GSTs' : Global_Source_Trees,
	'GXTR' : Extras,
	'LXTR' : Build_Extras,
	'MbFn' : member_function,
	'PATH' : Access_Paths,
	'PInf' : Path_Information,
	'PSTG' : Plugin_Settings,
	'RSTG' : Runtime_Settings,
	'RlPt' : Relative_Path,
	'SFit' : Shielded_Folder,
	'SHFL' : Shielded_Folders,
	'SNTX' : Syntax_Coloring,
	'Seg ' : Segment,
	'SrcF' : ProjectFile,
	'SrcT' : Source_Tree,
	'TARG' : Target_Settings,
	'TSTs' : Target_Source_Trees,
	'VCSs' : VCS_Setup,
	'mFNT' : Font,
}

_propdeclarations = {
	'Acce' : access,
	'BW00' : Browser_Keywords,
	'BW01' : Classes_Color,
	'BW02' : Constants_Color,
	'BW03' : Enums_Color,
	'BW04' : Functions_Color,
	'BW05' : Globals_Color,
	'BW06' : Macros_Color,
	'BW07' : Templates_Color,
	'BW08' : Typedefs_Color,
	'BW10' : Template_Commands_in_Menu,
	'BX01' : Completion_Sound,
	'BX02' : Success_Sound,
	'BX03' : Failure_Sound,
	'BX04' : Build_Before_Running,
	'BX05' : Include_Cache_Size,
	'BX06' : Compiler_Thread_Stack_Size,
	'BX07' : Save_Before_Building,
	'Bfor' : initialize_before,
	'CSiz' : codesize,
	'Clas' : class_,
	'DSiz' : datasize,
	'Db01' : Show_Variable_Types,
	'Db02' : Sort_By_Method,
	'Db03' : Use_RTTI,
	'Db04' : Threads_in_Window,
	'Db05' : Variable_Hints,
	'Db06' : Watchpoint_Hilite,
	'Db07' : Variable_Changed_Hilite,
	'Db08' : Default_Array_Size,
	'Db09' : Show_Locals,
	'Db10' : Show_As_Decimal,
	'DcEn' : declaration_end_offset,
	'DcFl' : declaration_file,
	'DcSt' : declaration_start_offset,
	'DfEn' : implementation_end_offset,
	'DfFl' : implementation_file,
	'DfSt' : implementation_start_offset,
	'Dg01' : Ignore_Mod_Dates,
	'Dg02' : Open_All_Classes,
	'Dg03' : Launch_Apps_on_Open,
	'Dg04' : Confirm_Kill,
	'Dg05' : Stop_at_Main,
	'Dg06' : Select_Stack_Crawl,
	'Dg07' : Dont_Step_in_Runtime,
	'Dg11' : Auto_Target_Libraries,
	'Dg12' : Cache_Edited_Files,
	'Dg13' : File_Cache_Duration,
	'Dt02' : Log_System_Messages,
	'Dt08' : Update_Data_While_Running,
	'Dt09' : Data_Update_Interval,
	'Dt10' : Relocated_Executable_Path,
	'Dt13' : Stop_at_temp_breakpoint,
	'Dt14' : Temp_breakpoint_names,
	'Dt15' : Cache_symbolics,
	'Dt16' : Temp_Breakpoint_Type,
	'Dw01' : Debugging_Start_Action,
	'Dw02' : Do_Nothing_To_Projects,
	'ED01' : Flash_Delay,
	'ED02' : Dynamic_Scroll,
	'ED03' : Balance,
	'ED04' : Use_Drag__26__Drop_Editing,
	'ED06' : Sort_Function_Popup,
	'ED07' : Use_Multiple_Undo,
	'ED08' : Remember_Font,
	'ED09' : Remember_Selection,
	'ED10' : Remember_Window,
	'ED12' : Main_Text_Color,
	'ED13' : Background_Color,
	'ED14' : Context_Popup_Delay,
	'ED15' : Relaxed_C_Popup_Parsing,
	'ED16' : Left_Margin_Line_Select,
	'ED17' : Default_Text_File_Format,
	'EX04' : Modification_Date_Caching,
	'EX07' : Full_Screen_Zoom,
	'EX08' : External_Reference,
	'EX09' : Browser_Active,
	'EX10' : Use_Editor_Extensions,
	'EX11' : Use_External_Editor,
	'EX12' : Use_Script_Menu,
	'EX16' : Recent_Editor_Count,
	'EX17' : Recent_Project_Count,
	'EX18' : Use_ToolServer_Menu,
	'EX19' : Automatic_Toolbar_Help,
	'EX30' : Dump_Browser_Info,
	'EX31' : Cache_Subproject_Data,
	'ErrL' : lineNumber,
	'ErrS' : message,
	'ErrT' : messageKind,
	'FMps' : Mappings,
	'FN01' : Auto_Indent,
	'FN02' : Tab_Size,
	'FN03' : Tab_Indents_Selection,
	'FN04' : Tab_Inserts_Spaces,
	'Frmt' : format,
	'Frmw' : framework,
	'GH01' : Syntax_Coloring,
	'GH02' : Comment_Color,
	'GH03' : Keyword_Color,
	'GH04' : String_Color,
	'GH05' : Custom_Color_1,
	'GH06' : Custom_Color_2,
	'GH07' : Custom_Color_3,
	'GH08' : Custom_Color_4,
	'HstF' : host_flags,
	'IncF' : includes,
	'Kind' : path_kind,
	'Lang' : language,
	'NumF' : filecount,
	'Orig' : origin,
	'PA01' : User_Paths,
	'PA02' : Always_Full_Search,
	'PA03' : System_Paths,
	'PA04' : Convert_Paths,
	'PA05' : Require_Framework_Includes,
	'PLck' : seg_2d_locked,
	'PR04' : File_Type,
	'PX01' : Plugin_Diagnostics_Level,
	'PX02' : Disable_Third_Party_COM_Plugins,
	'Path' : path,
	'Prel' : seg_2d_preloaded,
	'Prot' : seg_2d_protected,
	'Purg' : seg_2d_purgeable,
	'RS01' : Host_Application,
	'RS02' : Command_Line_Arguments,
	'RS03' : Working_Directory,
	'RS04' : Environment_Variables,
	'Recu' : recursive,
	'Root' : root,
	'SF01' : Expression_To_Match,
	'SF02' : Skip_Project_Operations,
	'SF03' : Skip_Find_And_Compare_Operations,
	'SFis' : Shielded_Items,
	'ST01' : Source_Trees,
	'SrcT' : filetype,
	'Stat' : static,
	'SubA' : all_subclasses,
	'SubC' : subclasses,
	'SymG' : symbols,
	'SysH' : seg_2d_system_heap,
	'TA01' : Linker,
	'TA02' : Extension,
	'TA03' : Precompiled,
	'TA04' : Resource_File,
	'TA05' : Launchable,
	'TA06' : Ignored_by_Make,
	'TA07' : Compiler,
	'TA09' : Post_Linker,
	'TA10' : Target_Name,
	'TA11' : Output_Directory_Path,
	'TA12' : Output_Directory_Origin,
	'TA13' : Pre_Linker,
	'TA15' : Use_Relative_Paths,
	'TA16' : Output_Directory_Location,
	'UpTD' : up_to_date,
	'VC01' : VCS_Active,
	'VC02' : Connection_Method,
	'VC03' : Username,
	'VC04' : Password,
	'VC05' : Auto_Connect,
	'VC06' : Store_Password,
	'VC07' : Always_Prompt,
	'VC08' : Mount_Volume,
	'VC09' : Database_Path,
	'VC10' : Local_Path,
	'VC11' : Use_Global_Settings,
	'Valu' : value,
	'Virt' : virtual,
	'Weak' : weak_link,
	'file' : disk_file,
	'pnam' : name,
	'ptps' : Text_Size,
	'ptxf' : Text_Font,
}

_compdeclarations = {
}

_enumdeclarations = {
	'Acce' : _Enum_Acce,
	'BXbr' : _Enum_BXbr,
	'DbSA' : _Enum_DbSA,
	'DgBL' : _Enum_DgBL,
	'ErrT' : _Enum_ErrT,
	'Inte' : _Enum_Inte,
	'Lang' : _Enum_Lang,
	'PPrm' : _Enum_PPrm,
	'PXdg' : _Enum_PXdg,
	'PthF' : _Enum_PthF,
	'RefP' : _Enum_RefP,
	'STKd' : _Enum_STKd,
	'SrcT' : _Enum_SrcT,
	'TmpB' : _Enum_TmpB,
	'TxtF' : _Enum_TxtF,
	'savo' : _Enum_savo,
}
