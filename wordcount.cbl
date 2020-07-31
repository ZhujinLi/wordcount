      * Run with Visual Cobol + Visual Studio 2019 + Windows 10

       copy cblproto.

       identification division.
       program-id. wordcount.

       environment division.
       input-output section.
       file-control.
       select text-file assign to entry-data-name-text
       organization is line sequential.

       data division.
       file section.
           fd text-file record contains 80 characters.
       01 text-file-line pic x(80).

       working-storage section.
       01 dir-handle pointer.
       01 dir-name-pattern.
         10 dir-name-pattern-length pic 9(4) comp-5.
         10 dir-name-pattern-text pic x(64).
       01 search-status pic x(2) comp-5.
       01 entry-data.
         10 entry-data-attribute pic x(4) comp-5.
         10 entry-data-date-stamp.
           20 entry-data-date-stamp-year pic x(4) comp-5.
           20 entry-data-date-stamp-month pic x(2) comp-5.
           20 entry-data-date-stamp-day pic x(2) comp-5.
           20 entry-data-date-stamp-hour pic x(2) comp-5.
           20 entry-data-date-stamp-minute pic x(2) comp-5.
           20 entry-data-date-stamp-sec pic x(2) comp-5.
           20 entry-data-date-stamp-msec pic x(2) comp-5.
           20 entry-data-date-stamp-dst pic x(1) comp-5.
           20 entry-data-date-stamp-size pic x(8) comp-5.
         10 entry-data-name.
           20 entry-data-name-length pic 9(4) comp-5 value 64.
           20 entry-data-name-text pic x(64).
       01 dir-queue-head pic 9(4) comp-5 value 1.
       01 dir-queue-tail pic 9(4) comp-5 value 1.
       01 dir-queue pic x(64) occurs 100 times.
       01 str-len pic 9(4) comp-5.
       01 is-eof pic 9 comp-5.
       01 word-ptr pic 9(4) comp-5.
       01 word-idx pic 9(4) comp-5.
       01 word pic x(80).
       01 res-words pic x(80) occurs 1000 times.
       01 res-counts pic 9(4) comp-5 occurs 1000 times value zeros.
       01 res-size pic 9(4) comp-5 value zero.
       01 i pic 9(4) comp-5.

       procedure division.
      * Initialize root directory
           move './testdata/' to dir-queue(1).

      * Search and process files recursively
           perform walk-dir until dir-queue-head > dir-queue-tail.

      * Print result
           perform varying i from 1 by 1 until i > res-size
               display res-counts(i) ' ' res-words(i)
           end-perform.

           stop run.

       walk-dir.
           move dir-queue(dir-queue-head) to dir-name-pattern-text
           add 1 to dir-queue-head.

           move function length (function trim (dir-name-pattern-text
             trailing)) to dir-name-pattern-length.

           call 'CBL_DIR_SCAN_START' using dir-handle
                                           dir-name-pattern
      * Scan files and directories
                                           3
      * Include the path in file names
                                           4
                                 returning search-status.

           perform next-entry until search-status <> zero.

           call 'CBL_DIR_SCAN_END' using dir-handle
                               returning search-status.

           exit paragraph.

       next-entry.
      * Initialize name-text; function does not right-pad to length.
           move spaces to entry-data-name-text.

      * Do the read.
           call 'CBL_DIR_SCAN_READ' using dir-handle
                                          entry-data
                                returning search-status
           if search-status <> zero
               exit paragraph.

           evaluate function mod (entry-data-attribute, 3)
      * File
               when 1
                   perform process-file
      * Directory
               when 2
                   move function length (function trim (
                       entry-data-name-text trailing)) to str-len
      * Skip . and ..
                   if not entry-data-name-text(str-len:1) = '.' then
                       add 1 to dir-queue-tail
                       move entry-data-name-text
                         to dir-queue(dir-queue-tail)
                   end-if.

           exit paragraph.

       process-file.
           open input text-file.

           move 0 to is-eof
           perform until is-eof = 1
               read text-file
                   at end
                       move 1 to is-eof
               end-read
               if is-eof = 0 then
                   perform process-line
           end-perform.

           close text-file.

           exit paragraph.

       process-line.
           move 1 to word-ptr.

      * A line of 80 chars has at most 40 words
           perform varying word-idx from 1 by 1 until word-idx > 40
               unstring text-file-line delimited by space
                 into word with pointer word-ptr
               if word not equal ' ' then
                   perform add-word
           end-perform.

           exit paragraph.

       add-word.
           perform varying i from 1 by 1
             until i > res-size or res-words(i) = word
           end-perform.

           if i > res-size then
               add 1 to res-size
               move word to res-words(res-size)
           end-if
           add 1 to res-counts(i).

           exit paragraph.
