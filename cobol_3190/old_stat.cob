identification division.

program-id. text-stats.


environment division.

input-output section.
  file-control.
  select input-file assign to "text.txt"
    organization is line sequential.
  select output-file assign to "out.txt"
    organization is sequential
    access mode is sequential.


data division.

file section.
  fd input-file.
    01 sample-input pic x(80).
  fd output-file.
    01 output-line pic x(80).

working-storage section.
  77 eof-switch pic 9 value 1.
  77 exit-switch pic 9.
  01 no-of-sentences pic s9(7) comp.
  01 no-of-words pic s9(7) comp.
  01 no-of-characters pic s9(7) comp.
  01 k pic s9(2) comp.
  01 input-area.
    02 line1 pic x occurs 80 times.
  01 output-title-line.
    02 filler pic x(31) value spaces.
    02 filler pic x(19) value "input text analyzed".
  01 output-underline.
    02 filler pic x(41) value " ----------------------------------------".
    02 filler pic x(40) value "----------------------------------------".
  01 output-area.
    02 filler pic x value space.
    02 out-line pic x(80).
  01 output-statistics-line-1.
    02 filler pic x(20) value spaces.
    02 filler pic x(20) value "number of sentences=".
    02 out-no-senten pic -(7)9.
  01 output-statistics-line-2.
    02 filler pic x(19) value spaces.
    02 filler pic x(33) value "number of words=".
    02 out-no-word pic -(7)9.
  01 output-statistics-line-3.
    02 filler pic x(19) value spaces.
    02 filler pic x(33) value "number of chars=".
    02 out-no-char pic -(7)9.
  01 output-statistics-line-4.
    02 filler pic x(19) value spaces.
    02 filler pic x(33) value "average number of words/sentence=".
    02 aver-words-se pic -(4)9.9(2).
  01 output-statistics-line-5.
    02 filler pic x(20) value spaces.
    02 filler pic x(31) value "average number of symbols/word=".
    02 aver-char-wor pic -(4)9.9(2).


procedure division.

open input input-file.
open output output-file.
move 2 to exit-switch.
perform proc-body until exit-switch is equal to 3.

proc-body.
  move zeroes to no-of-sentences, no-of-words, no-of-characters.
  move 81 to k.
  write output-line from output-title-line after advancing 0 lines.
  write output-line from output-underline after advancing 1 line.
  move 2 to exit-switch.
  perform outer-loop until exit-switch is equal to zero.

outer-loop.
  read input-file into input-area at end perform end-of-job.
  move input-area to out-line.
  write output-line from output-area after advancing 1 line.
  subtract 80 from k.
  perform new-sentence-proc until exit-switch is equal to zero
                                  or k is greater than 80.

new-sentence-proc.
  move 2 to exit-switch.
  if line1(k) is not equal to "/"
    perform process-loop
    until k is greater than 80 or exit-switch is less than 2
  else
    perform output-statistics-proc
  end-if.

output-statistics-proc.
  move no-of-sentences to out-no-senten.
  move no-of-words to out-no-word.
  move no-of-characters to out-no-char.
  divide no-of-sentences into no-of-words
  giving aver-words-se rounded.
  divide no-of-words into no-of-characters
  giving aver-char-wor rounded.
  write output-line from output-underline after advancing 1 line.
  write output-line from output-statistics-line-1 after advancing 1 line.
  write output-line from output-statistics-line-2 after advancing 1 line.
  write output-line from output-statistics-line-3 after advancing 1 line.
  write output-line from output-statistics-line-4 after advancing 1 line.
  write output-line from output-statistics-line-5 after advancing 1 line.
  write output-line from output-underline after advancing 1 line.
  move zero to exit-switch.

process-loop.
  if line1(k) = space
    add 1 to no-of-words
    add 1 to k
  else if line1(k) not = "."
    add 1 to k
    if line1(k) not = "," and not = ";" and not = "-"
      add 1 to no-of-characters
    end-if
  else
    add 1 to no-of-sentences
    add 1 to no-of-words
    add 3 to k
    move 1 to exit-switch
  end-if.

end-of-job.
  close input-file, output-file.

stop run.