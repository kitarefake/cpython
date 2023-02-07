// This file is generated by Tools/cases_generator/generate_cases.py --metadata
// from Python/bytecodes.c
// Do not edit!

#ifndef NDEBUG
static int
_PyOpcode_num_popped(int opcode, int oparg, bool jump) {
    switch(opcode) {
        case NOP:
            return 0;
        case RESUME:
            return 0;
        case LOAD_CLOSURE:
            return 0;
        case LOAD_FAST_CHECK:
            return 0;
        case LOAD_FAST:
            return 0;
        case LOAD_CONST:
            return 0;
        case STORE_FAST:
            return 1;
        case LOAD_FAST__LOAD_FAST:
            return 0+0;
        case LOAD_FAST__LOAD_CONST:
            return 0+0;
        case STORE_FAST__LOAD_FAST:
            return 1+0;
        case STORE_FAST__STORE_FAST:
            return 1+1;
        case LOAD_CONST__LOAD_FAST:
            return 0+0;
        case POP_TOP:
            return 1;
        case PUSH_NULL:
            return 0;
        case END_FOR:
            return 1+1;
        case UNARY_NEGATIVE:
            return 1;
        case UNARY_NOT:
            return 1;
        case UNARY_INVERT:
            return 1;
        case BINARY_OP_MULTIPLY_INT:
            return 2;
        case BINARY_OP_MULTIPLY_FLOAT:
            return 2;
        case BINARY_OP_SUBTRACT_INT:
            return 2;
        case BINARY_OP_SUBTRACT_FLOAT:
            return 2;
        case BINARY_OP_ADD_UNICODE:
            return 2;
        case BINARY_OP_INPLACE_ADD_UNICODE:
            return 2;
        case BINARY_OP_ADD_FLOAT:
            return 2;
        case BINARY_OP_ADD_INT:
            return 2;
        case BINARY_SUBSCR:
            return 2;
        case BINARY_SLICE:
            return 3;
        case STORE_SLICE:
            return 4;
        case BINARY_SUBSCR_LIST_INT:
            return 2;
        case BINARY_SUBSCR_TUPLE_INT:
            return 2;
        case BINARY_SUBSCR_DICT:
            return 2;
        case BINARY_SUBSCR_GETITEM:
            return 2;
        case LIST_APPEND:
            return (oparg-1) + 2;
        case SET_ADD:
            return (oparg-1) + 2;
        case STORE_SUBSCR:
            return 3;
        case STORE_SUBSCR_LIST_INT:
            return 3;
        case STORE_SUBSCR_DICT:
            return 3;
        case DELETE_SUBSCR:
            return 2;
        case CALL_INTRINSIC_1:
            return 1;
        case RAISE_VARARGS:
            return oparg;
        case INTERPRETER_EXIT:
            return 1;
        case RETURN_VALUE:
            return 1;
        case RETURN_CONST:
            return 0;
        case GET_AITER:
            return 1;
        case GET_ANEXT:
            return 1;
        case GET_AWAITABLE:
            return 1;
        case SEND:
            return 2;
        case YIELD_VALUE:
            return 1;
        case POP_EXCEPT:
            return 1;
        case RERAISE:
            return oparg + 1;
        case PREP_RERAISE_STAR:
            return 2;
        case END_ASYNC_FOR:
            return 2;
        case CLEANUP_THROW:
            return 3;
        case LOAD_ASSERTION_ERROR:
            return 0;
        case LOAD_BUILD_CLASS:
            return 0;
        case STORE_NAME:
            return 1;
        case DELETE_NAME:
            return 0;
        case UNPACK_SEQUENCE:
            return 1;
        case UNPACK_SEQUENCE_TWO_TUPLE:
            return 1;
        case UNPACK_SEQUENCE_TUPLE:
            return -1;
        case UNPACK_SEQUENCE_LIST:
            return -1;
        case UNPACK_EX:
            return 1;
        case STORE_ATTR:
            return 2;
        case DELETE_ATTR:
            return 1;
        case STORE_GLOBAL:
            return 1;
        case DELETE_GLOBAL:
            return 0;
        case LOAD_NAME:
            return 0;
        case LOAD_GLOBAL:
            return 0;
        case LOAD_GLOBAL_MODULE:
            return 0;
        case LOAD_GLOBAL_BUILTIN:
            return 0;
        case DELETE_FAST:
            return 0;
        case MAKE_CELL:
            return 0;
        case DELETE_DEREF:
            return 0;
        case LOAD_CLASSDEREF:
            return 0;
        case LOAD_DEREF:
            return 0;
        case STORE_DEREF:
            return 1;
        case COPY_FREE_VARS:
            return 0;
        case BUILD_STRING:
            return oparg;
        case BUILD_TUPLE:
            return oparg;
        case BUILD_LIST:
            return oparg;
        case LIST_EXTEND:
            return (oparg-1) + 2;
        case SET_UPDATE:
            return (oparg-1) + 2;
        case BUILD_SET:
            return oparg;
        case BUILD_MAP:
            return oparg*2;
        case SETUP_ANNOTATIONS:
            return 0;
        case BUILD_CONST_KEY_MAP:
            return oparg + 1;
        case DICT_UPDATE:
            return 1;
        case DICT_MERGE:
            return 1;
        case MAP_ADD:
            return 2;
        case LOAD_ATTR:
            return 1;
        case LOAD_ATTR_INSTANCE_VALUE:
            return 1;
        case LOAD_ATTR_MODULE:
            return 1;
        case LOAD_ATTR_WITH_HINT:
            return 1;
        case LOAD_ATTR_SLOT:
            return 1;
        case LOAD_ATTR_CLASS:
            return 1;
        case LOAD_ATTR_PROPERTY:
            return 1;
        case LOAD_ATTR_GETATTRIBUTE_OVERRIDDEN:
            return 1;
        case STORE_ATTR_INSTANCE_VALUE:
            return 2;
        case STORE_ATTR_WITH_HINT:
            return 2;
        case STORE_ATTR_SLOT:
            return 2;
        case COMPARE_OP:
            return 2;
        case COMPARE_AND_BRANCH:
            return 2;
        case COMPARE_AND_BRANCH_FLOAT:
            return 2;
        case COMPARE_AND_BRANCH_INT:
            return 2;
        case COMPARE_AND_BRANCH_STR:
            return 2;
        case IS_OP:
            return 2;
        case CONTAINS_OP:
            return 2;
        case CHECK_EG_MATCH:
            return 2;
        case CHECK_EXC_MATCH:
            return 2;
        case IMPORT_NAME:
            return 2;
        case IMPORT_FROM:
            return 1;
        case JUMP_FORWARD:
            return 0;
        case JUMP_BACKWARD:
            return 0;
        case POP_JUMP_IF_FALSE:
            return 1;
        case POP_JUMP_IF_TRUE:
            return 1;
        case POP_JUMP_IF_NOT_NONE:
            return 1;
        case POP_JUMP_IF_NONE:
            return 1;
        case JUMP_IF_FALSE_OR_POP:
            return 1;
        case JUMP_IF_TRUE_OR_POP:
            return 1;
        case JUMP_BACKWARD_NO_INTERRUPT:
            return 0;
        case GET_LEN:
            return 1;
        case MATCH_CLASS:
            return 3;
        case MATCH_MAPPING:
            return 1;
        case MATCH_SEQUENCE:
            return 1;
        case MATCH_KEYS:
            return 2;
        case GET_ITER:
            return 1;
        case GET_YIELD_FROM_ITER:
            return 1;
        case FOR_ITER:
            return 1;
        case FOR_ITER_LIST:
            return 1;
        case FOR_ITER_TUPLE:
            return 1;
        case FOR_ITER_RANGE:
            return 1;
        case FOR_ITER_GEN:
            return 1;
        case BEFORE_ASYNC_WITH:
            return 1;
        case BEFORE_WITH:
            return 1;
        case WITH_EXCEPT_START:
            return 4;
        case PUSH_EXC_INFO:
            return 1;
        case LOAD_ATTR_METHOD_WITH_VALUES:
            return 1;
        case LOAD_ATTR_METHOD_NO_DICT:
            return 1;
        case LOAD_ATTR_METHOD_LAZY_DICT:
            return 1;
        case CALL_BOUND_METHOD_EXACT_ARGS:
            return -1;
        case KW_NAMES:
            return 0;
        case CALL:
            return -1;
        case CALL_PY_EXACT_ARGS:
            return -1;
        case CALL_PY_WITH_DEFAULTS:
            return -1;
        case CALL_NO_KW_TYPE_1:
            return -1;
        case CALL_NO_KW_STR_1:
            return -1;
        case CALL_NO_KW_TUPLE_1:
            return -1;
        case CALL_BUILTIN_CLASS:
            return -1;
        case CALL_NO_KW_BUILTIN_O:
            return -1;
        case CALL_NO_KW_BUILTIN_FAST:
            return -1;
        case CALL_BUILTIN_FAST_WITH_KEYWORDS:
            return -1;
        case CALL_NO_KW_LEN:
            return -1;
        case CALL_NO_KW_ISINSTANCE:
            return -1;
        case CALL_NO_KW_LIST_APPEND:
            return -1;
        case CALL_NO_KW_METHOD_DESCRIPTOR_O:
            return -1;
        case CALL_METHOD_DESCRIPTOR_FAST_WITH_KEYWORDS:
            return -1;
        case CALL_NO_KW_METHOD_DESCRIPTOR_NOARGS:
            return -1;
        case CALL_NO_KW_METHOD_DESCRIPTOR_FAST:
            return -1;
        case CALL_FUNCTION_EX:
            return -1;
        case MAKE_FUNCTION:
            return ((oparg & 0x01) ? 1 : 0) + ((oparg & 0x02) ? 1 : 0) + ((oparg & 0x04) ? 1 : 0) + ((oparg & 0x08) ? 1 : 0) + 1;
        case RETURN_GENERATOR:
            return 0;
        case BUILD_SLICE:
            return ((oparg == 3) ? 1 : 0) + 2;
        case FORMAT_VALUE:
            return -1;
        case COPY:
            return (oparg-1) + 1;
        case BINARY_OP:
            return 2;
        case SWAP:
            return (oparg-2) + 2;
        case EXTENDED_ARG:
            return 0;
        case CACHE:
            return 0;
        default:
            Py_UNREACHABLE();
    }
}
#endif

#ifndef NDEBUG
static int
_PyOpcode_num_pushed(int opcode, int oparg, bool jump) {
    switch(opcode) {
        case NOP:
            return 0;
        case RESUME:
            return 0;
        case LOAD_CLOSURE:
            return 1;
        case LOAD_FAST_CHECK:
            return 1;
        case LOAD_FAST:
            return 1;
        case LOAD_CONST:
            return 1;
        case STORE_FAST:
            return 0;
        case LOAD_FAST__LOAD_FAST:
            return 1+1;
        case LOAD_FAST__LOAD_CONST:
            return 1+1;
        case STORE_FAST__LOAD_FAST:
            return 0+1;
        case STORE_FAST__STORE_FAST:
            return 0+0;
        case LOAD_CONST__LOAD_FAST:
            return 1+1;
        case POP_TOP:
            return 0;
        case PUSH_NULL:
            return 1;
        case END_FOR:
            return 0+0;
        case UNARY_NEGATIVE:
            return 1;
        case UNARY_NOT:
            return 1;
        case UNARY_INVERT:
            return 1;
        case BINARY_OP_MULTIPLY_INT:
            return 1;
        case BINARY_OP_MULTIPLY_FLOAT:
            return 1;
        case BINARY_OP_SUBTRACT_INT:
            return 1;
        case BINARY_OP_SUBTRACT_FLOAT:
            return 1;
        case BINARY_OP_ADD_UNICODE:
            return 1;
        case BINARY_OP_INPLACE_ADD_UNICODE:
            return 0;
        case BINARY_OP_ADD_FLOAT:
            return 1;
        case BINARY_OP_ADD_INT:
            return 1;
        case BINARY_SUBSCR:
            return 1;
        case BINARY_SLICE:
            return 1;
        case STORE_SLICE:
            return 0;
        case BINARY_SUBSCR_LIST_INT:
            return 1;
        case BINARY_SUBSCR_TUPLE_INT:
            return 1;
        case BINARY_SUBSCR_DICT:
            return 1;
        case BINARY_SUBSCR_GETITEM:
            return 1;
        case LIST_APPEND:
            return (oparg-1) + 1;
        case SET_ADD:
            return (oparg-1) + 1;
        case STORE_SUBSCR:
            return 0;
        case STORE_SUBSCR_LIST_INT:
            return 0;
        case STORE_SUBSCR_DICT:
            return 0;
        case DELETE_SUBSCR:
            return 0;
        case CALL_INTRINSIC_1:
            return 1;
        case RAISE_VARARGS:
            return 0;
        case INTERPRETER_EXIT:
            return 0;
        case RETURN_VALUE:
            return 0;
        case RETURN_CONST:
            return 0;
        case GET_AITER:
            return 1;
        case GET_ANEXT:
            return 2;
        case GET_AWAITABLE:
            return 1;
        case SEND:
            return ((!jump) ? 1 : 0) + 1;
        case YIELD_VALUE:
            return 1;
        case POP_EXCEPT:
            return 0;
        case RERAISE:
            return oparg;
        case PREP_RERAISE_STAR:
            return 1;
        case END_ASYNC_FOR:
            return 0;
        case CLEANUP_THROW:
            return 1;
        case LOAD_ASSERTION_ERROR:
            return 1;
        case LOAD_BUILD_CLASS:
            return 1;
        case STORE_NAME:
            return 0;
        case DELETE_NAME:
            return 0;
        case UNPACK_SEQUENCE:
            return oparg;
        case UNPACK_SEQUENCE_TWO_TUPLE:
            return 2;
        case UNPACK_SEQUENCE_TUPLE:
            return -1;
        case UNPACK_SEQUENCE_LIST:
            return -1;
        case UNPACK_EX:
            return (oparg & 0xFF) + (oparg >> 8) + 1;
        case STORE_ATTR:
            return 0;
        case DELETE_ATTR:
            return 0;
        case STORE_GLOBAL:
            return 0;
        case DELETE_GLOBAL:
            return 0;
        case LOAD_NAME:
            return 1;
        case LOAD_GLOBAL:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_GLOBAL_MODULE:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_GLOBAL_BUILTIN:
            return ((oparg & 1) ? 1 : 0) + 1;
        case DELETE_FAST:
            return 0;
        case MAKE_CELL:
            return 0;
        case DELETE_DEREF:
            return 0;
        case LOAD_CLASSDEREF:
            return 1;
        case LOAD_DEREF:
            return 1;
        case STORE_DEREF:
            return 0;
        case COPY_FREE_VARS:
            return 0;
        case BUILD_STRING:
            return 1;
        case BUILD_TUPLE:
            return 1;
        case BUILD_LIST:
            return 1;
        case LIST_EXTEND:
            return (oparg-1) + 1;
        case SET_UPDATE:
            return (oparg-1) + 1;
        case BUILD_SET:
            return 1;
        case BUILD_MAP:
            return 1;
        case SETUP_ANNOTATIONS:
            return 0;
        case BUILD_CONST_KEY_MAP:
            return 1;
        case DICT_UPDATE:
            return 0;
        case DICT_MERGE:
            return 0;
        case MAP_ADD:
            return 0;
        case LOAD_ATTR:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_INSTANCE_VALUE:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_MODULE:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_WITH_HINT:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_SLOT:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_CLASS:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_PROPERTY:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_GETATTRIBUTE_OVERRIDDEN:
            return ((oparg & 1) ? 1 : 0) + 1;
        case STORE_ATTR_INSTANCE_VALUE:
            return 0;
        case STORE_ATTR_WITH_HINT:
            return 0;
        case STORE_ATTR_SLOT:
            return 0;
        case COMPARE_OP:
            return 1;
        case COMPARE_AND_BRANCH:
            return 0;
        case COMPARE_AND_BRANCH_FLOAT:
            return 0;
        case COMPARE_AND_BRANCH_INT:
            return 0;
        case COMPARE_AND_BRANCH_STR:
            return 0;
        case IS_OP:
            return 1;
        case CONTAINS_OP:
            return 1;
        case CHECK_EG_MATCH:
            return 2;
        case CHECK_EXC_MATCH:
            return 2;
        case IMPORT_NAME:
            return 1;
        case IMPORT_FROM:
            return 2;
        case JUMP_FORWARD:
            return 0;
        case JUMP_BACKWARD:
            return 0;
        case POP_JUMP_IF_FALSE:
            return 0;
        case POP_JUMP_IF_TRUE:
            return 0;
        case POP_JUMP_IF_NOT_NONE:
            return 0;
        case POP_JUMP_IF_NONE:
            return 0;
        case JUMP_IF_FALSE_OR_POP:
            return (jump ? 1 : 0);
        case JUMP_IF_TRUE_OR_POP:
            return (jump ? 1 : 0);
        case JUMP_BACKWARD_NO_INTERRUPT:
            return 0;
        case GET_LEN:
            return 2;
        case MATCH_CLASS:
            return 1;
        case MATCH_MAPPING:
            return 2;
        case MATCH_SEQUENCE:
            return 2;
        case MATCH_KEYS:
            return 3;
        case GET_ITER:
            return 1;
        case GET_YIELD_FROM_ITER:
            return 1;
        case FOR_ITER:
            return 2;
        case FOR_ITER_LIST:
            return 2;
        case FOR_ITER_TUPLE:
            return 2;
        case FOR_ITER_RANGE:
            return 2;
        case FOR_ITER_GEN:
            return 2;
        case BEFORE_ASYNC_WITH:
            return 2;
        case BEFORE_WITH:
            return 2;
        case WITH_EXCEPT_START:
            return 5;
        case PUSH_EXC_INFO:
            return 2;
        case LOAD_ATTR_METHOD_WITH_VALUES:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_METHOD_NO_DICT:
            return ((oparg & 1) ? 1 : 0) + 1;
        case LOAD_ATTR_METHOD_LAZY_DICT:
            return ((oparg & 1) ? 1 : 0) + 1;
        case CALL_BOUND_METHOD_EXACT_ARGS:
            return -1;
        case KW_NAMES:
            return 0;
        case CALL:
            return -1;
        case CALL_PY_EXACT_ARGS:
            return -1;
        case CALL_PY_WITH_DEFAULTS:
            return -1;
        case CALL_NO_KW_TYPE_1:
            return -1;
        case CALL_NO_KW_STR_1:
            return -1;
        case CALL_NO_KW_TUPLE_1:
            return -1;
        case CALL_BUILTIN_CLASS:
            return -1;
        case CALL_NO_KW_BUILTIN_O:
            return -1;
        case CALL_NO_KW_BUILTIN_FAST:
            return -1;
        case CALL_BUILTIN_FAST_WITH_KEYWORDS:
            return -1;
        case CALL_NO_KW_LEN:
            return -1;
        case CALL_NO_KW_ISINSTANCE:
            return -1;
        case CALL_NO_KW_LIST_APPEND:
            return -1;
        case CALL_NO_KW_METHOD_DESCRIPTOR_O:
            return -1;
        case CALL_METHOD_DESCRIPTOR_FAST_WITH_KEYWORDS:
            return -1;
        case CALL_NO_KW_METHOD_DESCRIPTOR_NOARGS:
            return -1;
        case CALL_NO_KW_METHOD_DESCRIPTOR_FAST:
            return -1;
        case CALL_FUNCTION_EX:
            return -1;
        case MAKE_FUNCTION:
            return 1;
        case RETURN_GENERATOR:
            return 0;
        case BUILD_SLICE:
            return 1;
        case FORMAT_VALUE:
            return -1;
        case COPY:
            return (oparg-1) + 2;
        case BINARY_OP:
            return 1;
        case SWAP:
            return (oparg-2) + 2;
        case EXTENDED_ARG:
            return 0;
        case CACHE:
            return 0;
        default:
            Py_UNREACHABLE();
    }
}
#endif
enum Direction { DIR_NONE, DIR_READ, DIR_WRITE };
enum InstructionFormat { INSTR_FMT_IB, INSTR_FMT_IBC, INSTR_FMT_IBC0, INSTR_FMT_IBC000, INSTR_FMT_IBC0000, INSTR_FMT_IBC00000000, INSTR_FMT_IBIB, INSTR_FMT_IX, INSTR_FMT_IXC, INSTR_FMT_IXC000 };
struct opcode_metadata {
    enum Direction dir_op1;
    enum Direction dir_op2;
    enum Direction dir_op3;
    bool valid_entry;
    enum InstructionFormat instr_format;
} _PyOpcode_opcode_metadata[256] = {
    [NOP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [RESUME] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_CLOSURE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_FAST_CHECK] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_CONST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [STORE_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_FAST__LOAD_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBIB },
    [LOAD_FAST__LOAD_CONST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBIB },
    [STORE_FAST__LOAD_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBIB },
    [STORE_FAST__STORE_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBIB },
    [LOAD_CONST__LOAD_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBIB },
    [POP_TOP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [PUSH_NULL] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [END_FOR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [UNARY_NEGATIVE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [UNARY_NOT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [UNARY_INVERT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [BINARY_OP_MULTIPLY_INT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [BINARY_OP_MULTIPLY_FLOAT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [BINARY_OP_SUBTRACT_INT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [BINARY_OP_SUBTRACT_FLOAT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [BINARY_OP_ADD_UNICODE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [BINARY_OP_INPLACE_ADD_UNICODE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [BINARY_OP_ADD_FLOAT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [BINARY_OP_ADD_INT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [BINARY_SUBSCR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC000 },
    [BINARY_SLICE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [STORE_SLICE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [BINARY_SUBSCR_LIST_INT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC000 },
    [BINARY_SUBSCR_TUPLE_INT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC000 },
    [BINARY_SUBSCR_DICT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC000 },
    [BINARY_SUBSCR_GETITEM] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC000 },
    [LIST_APPEND] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [SET_ADD] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [STORE_SUBSCR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [STORE_SUBSCR_LIST_INT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [STORE_SUBSCR_DICT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [DELETE_SUBSCR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [CALL_INTRINSIC_1] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [RAISE_VARARGS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [INTERPRETER_EXIT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [RETURN_VALUE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [RETURN_CONST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [GET_AITER] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [GET_ANEXT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [GET_AWAITABLE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [SEND] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [YIELD_VALUE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [POP_EXCEPT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [RERAISE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [PREP_RERAISE_STAR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [END_ASYNC_FOR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [CLEANUP_THROW] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [LOAD_ASSERTION_ERROR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [LOAD_BUILD_CLASS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [STORE_NAME] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [DELETE_NAME] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [UNPACK_SEQUENCE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC },
    [UNPACK_SEQUENCE_TWO_TUPLE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC },
    [UNPACK_SEQUENCE_TUPLE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [UNPACK_SEQUENCE_LIST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [UNPACK_EX] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [STORE_ATTR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC000 },
    [DELETE_ATTR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [STORE_GLOBAL] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [DELETE_GLOBAL] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_NAME] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_GLOBAL] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC0000 },
    [LOAD_GLOBAL_MODULE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC0000 },
    [LOAD_GLOBAL_BUILTIN] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC0000 },
    [DELETE_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [MAKE_CELL] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [DELETE_DEREF] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_CLASSDEREF] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_DEREF] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [STORE_DEREF] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [COPY_FREE_VARS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [BUILD_STRING] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [BUILD_TUPLE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [BUILD_LIST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LIST_EXTEND] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [SET_UPDATE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [BUILD_SET] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [BUILD_MAP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [SETUP_ANNOTATIONS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [BUILD_CONST_KEY_MAP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [DICT_UPDATE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [DICT_MERGE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [MAP_ADD] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [LOAD_ATTR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_INSTANCE_VALUE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_MODULE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_WITH_HINT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_SLOT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_CLASS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_PROPERTY] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_GETATTRIBUTE_OVERRIDDEN] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [STORE_ATTR_INSTANCE_VALUE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC000 },
    [STORE_ATTR_WITH_HINT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC000 },
    [STORE_ATTR_SLOT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IXC000 },
    [COMPARE_OP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC },
    [COMPARE_AND_BRANCH] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC0 },
    [COMPARE_AND_BRANCH_FLOAT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC0 },
    [COMPARE_AND_BRANCH_INT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC0 },
    [COMPARE_AND_BRANCH_STR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC0 },
    [IS_OP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CONTAINS_OP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CHECK_EG_MATCH] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [CHECK_EXC_MATCH] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [IMPORT_NAME] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [IMPORT_FROM] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [JUMP_FORWARD] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [JUMP_BACKWARD] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [POP_JUMP_IF_FALSE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [POP_JUMP_IF_TRUE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [POP_JUMP_IF_NOT_NONE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [POP_JUMP_IF_NONE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [JUMP_IF_FALSE_OR_POP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [JUMP_IF_TRUE_OR_POP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [JUMP_BACKWARD_NO_INTERRUPT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [GET_LEN] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [MATCH_CLASS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [MATCH_MAPPING] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [MATCH_SEQUENCE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [MATCH_KEYS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [GET_ITER] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [GET_YIELD_FROM_ITER] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [FOR_ITER] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC },
    [FOR_ITER_LIST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC },
    [FOR_ITER_TUPLE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC },
    [FOR_ITER_RANGE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC },
    [FOR_ITER_GEN] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC },
    [BEFORE_ASYNC_WITH] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [BEFORE_WITH] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [WITH_EXCEPT_START] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [PUSH_EXC_INFO] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [LOAD_ATTR_METHOD_WITH_VALUES] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_METHOD_NO_DICT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [LOAD_ATTR_METHOD_LAZY_DICT] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC00000000 },
    [CALL_BOUND_METHOD_EXACT_ARGS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [KW_NAMES] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_PY_EXACT_ARGS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_PY_WITH_DEFAULTS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_TYPE_1] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_STR_1] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_TUPLE_1] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_BUILTIN_CLASS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_BUILTIN_O] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_BUILTIN_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_BUILTIN_FAST_WITH_KEYWORDS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_LEN] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_ISINSTANCE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_LIST_APPEND] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_METHOD_DESCRIPTOR_O] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_METHOD_DESCRIPTOR_FAST_WITH_KEYWORDS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_METHOD_DESCRIPTOR_NOARGS] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_NO_KW_METHOD_DESCRIPTOR_FAST] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CALL_FUNCTION_EX] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [MAKE_FUNCTION] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [RETURN_GENERATOR] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
    [BUILD_SLICE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [FORMAT_VALUE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [COPY] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [BINARY_OP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IBC },
    [SWAP] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [EXTENDED_ARG] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IB },
    [CACHE] = { DIR_NONE, DIR_NONE, DIR_NONE, true, INSTR_FMT_IX },
};
