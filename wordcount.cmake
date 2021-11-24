macro(ADD_WORD WORD)
    list(FIND RECORD_KEYS ${WORD} IDX)

    if (${IDX} EQUAL -1)
        set(COUNT 1)
    else()
        list(GET RECORD_VALUES ${IDX} COUNT)
        math(EXPR COUNT "${COUNT}+1")
        list(REMOVE_AT RECORD_KEYS ${IDX})
        list(REMOVE_AT RECORD_VALUES ${IDX})
    endif()

    list(APPEND RECORD_KEYS ${WORD})
    list(APPEND RECORD_VALUES ${COUNT})
endmacro()


file(GLOB_RECURSE FILES "./testdata/*")

foreach(FILE ${FILES})
    file(STRINGS ${FILE} CONTENT)
    separate_arguments(CONTENT)
    foreach(WORD ${CONTENT})
        add_word(${WORD})
    endforeach()
endforeach()

list(LENGTH RECORD_KEYS RECORD_KEYS_NUMBER)
math(EXPR RECORD_KEYS_NUMBER "${RECORD_KEYS_NUMBER}-1")

foreach(IDX RANGE ${RECORD_KEYS_NUMBER})
    list(GET RECORD_KEYS ${IDX} WORD)
    list(GET RECORD_VALUES ${IDX} COUNT)
    message("${WORD} ${COUNT}")
endforeach()