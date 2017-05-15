*> -----------------------------------------------------------------------------
*>         Name:  Ben Turcotte
*>   Student ID:  Bturcott
*>    Student #:  0832217
*>        Email:  bturcott@mail.uoguelph.ca
*>        Class:  CIS*3190
*>   Assignment:  3 - Cobol Re-engineering
*> -----------------------------------------------------------------------------


*> who am i? -------------------------------------------------------------------

identification division.
program-id. text-stats.


*> what things will i interact with? --------------------------------------------

environment division.
input-output section.
  file-control.
  select input-file assign to dynamic runtime-filename
    organization is line sequential.
  select output-file assign to "out.txt"
    organization is sequential
    access mode is sequential.


*> what things do I know? ------------------------------------------------------

data division.
file section.
  fd input-file.
    01 input-line  pic x(512).
  fd output-file.
    01 output-line pic x(512).

working-storage section.
  01 runtime-filename pic x(40) value "unassigned".
  01 filename-prompt  pic x(52) value "Type the name of the input file, then press <enter>.".
  01 header-text    pic x(512) value "                ---- start of input text ----".
  01 input-body.
    05 input-lines occurs 1024 times.
      10 input-char pic x       value space occurs 512 times.
  01 footer-text    pic x(512)  value "                 ---- end of input text ----".
  01 blank-line     pic x(512)  value spaces.
  01 bar1           pic x(512)  value " +----------------------------------------------------------+".
  01 title-line     pic x(512)  value " |                        statistics                        |".
  01 bar2           pic x(512)  value " +----------------------------------------------------------+".
  01 num-sents      pic x(512)  value " | number of sentences ....................... _DELIM_".
  01 num-words      pic x(512)  value " | number of words ........................... _DELIM_".
  01 num-chars      pic x(512)  value " | number of characters ...................... _DELIM_".
  01 num-numSs      pic x(512)  value " | number of numberic strings ................ _DELIM_".
  01 num-numCs      pic x(512)  value " | number of number characters ............... _DELIM_".
  01 words-sent     pic x(512)  value " | average number of words per sentence ...... _DELIM_".
  01 chars-word     pic x(512)  value " | average number of characters per word ..... _DELIM_".
  01 bar3           pic x(512)  value " +----------------------------------------------------------+".
  01 sent-count     pic 9(9)    value 0.
  01 word-count     pic 9(9)    value 0.
  01 char-count     pic 9(9)    value 0.
  01 numS-count     pic 9(9)    value 0.
  01 numC-count     pic 9(9)    value 0.
  01 avg-word-sent  pic 9(9).99.
  01 avg-char-word  pic 9(9).99.
  01 delim          pic x(7)    value "_DELIM_".
  01 buff.
    05 line-buff    pic x(512).
  01 remainstr.
    05 remainchars  pic x       value " " occurs 512 times.
  77 i              pic 9(4)    value 1.
  77 j              pic 9(4)    value 1.
  77 at-eof         pic 9       value 0.
  77 tally-x        pic 9(9)    value 0.


*> what am i to do with all this? ----------------------------------------------

procedure division.

perform until runtime-filename is not equal to "unassigned"
  move "unassigned" to runtime-filename
  display filename-prompt
  accept runtime-filename
end-perform.

open input input-file.
open output output-file.
move zeros to avg-word-sent, avg-char-word.


*> gather stats from file ------------------------------------------------------

perform until at-eof equals 1

  read input-file into buff
    at end
      move 1 to at-eof
    not at end
      move line-buff to input-lines(i)

*>    sentence count
      move 0 to tally-x
      inspect input-lines(i) tallying tally-x for all ". "
      inspect input-lines(i) tallying tally-x for all "? "
      inspect input-lines(i) tallying tally-x for all "! "
      add tally-x to sent-count

*>    word count & character count
      move input-lines(i) to remainstr
      perform with test before until remainstr equals spaces 
        add 1 to word-count
*>      run ahead until you hit a word
        move 1 to j
        perform until remainchars(j) is not equal to " " or j is greater than 512
          add 1 to j
        end-perform
*>      change all letters of the word to spaces
        perform until remainchars(j) equals " " or j is greater than 512
          move " " to remainchars(j)
          add 1 to char-count
          add 1 to j
        end-perform
      end-perform

*>    number character count
      move 0 to tally-x
      inspect input-lines(i) tallying tally-x for all '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
      add tally-x to numC-count

*>    number string count
      move 1 to j
      perform with test before until j is greater than 512 
        perform until input-char(i,j) is numeric or j is greater than 512
          add 1 to j
        end-perform
        if j is greater than 512 and input-char(i,512) is numeric
          add 1 to numS-count
        else if j is less than 513
          add 1 to numS-count
          perform until input-char(i,j) is not numeric
                    and input-char(i,j) is not equal to "-"
                    and input-char(i,j) is not equal to "."
            add 1 to j
            if j is greater than 512, then exit
          end-perform
        end-if
      end-perform

      add 1 to i

end-perform.


*> clean up stats --------------------------------------------------------------

*> update word count to get rid of numbers that were mistakenly counted as words
if numS-count is greater than zero and word-count is greater than or equal to numS-count
  subtract numS-count from word-count.

*> calculate averages
if word-count is greater than zero and sent-count is greater than zero
  divide word-count by sent-count giving avg-word-sent
else
  move 0 to avg-word-sent.

if char-count is greater than 0 and word-count is greater than 0
  divide char-count by word-count giving avg-char-word
else
  move 0 to avg-char-word.

*> insert a termination marker for printing
if i is less than 1025, then move "STOP_PRINTING" to input-lines(i)

*> convert leading zeros to spaces
inspect sent-count    replacing leading zero by space.
inspect word-count    replacing leading zero by space.
inspect char-count    replacing leading zero by space.
inspect numS-count    replacing leading zero by space.
inspect numC-count    replacing leading zero by space.
inspect avg-word-sent replacing leading zero by space.
inspect avg-char-word replacing leading zero by space.


*> Print stats to file ---------------------------------------------------------

write output-line from header-text after advancing 0 lines.

move 1 to i.
perform until i > 1024 or input-lines(i) equals "STOP_PRINTING"
  write output-line from input-lines(i) after advancing 1 line
  add 1 to i
end-perform.

write output-line from footer-text after advancing 1 line.
write output-line from blank-line  after advancing 1 line.
write output-line from bar1        after advancing 1 line.
write output-line from title-line  after advancing 1 line.
write output-line from bar2        after advancing 1 line.

if sent-count is equal to spaces
  move " | no sentences were found                     _DELIM_" to num-sents.
string num-sents delimited by delim, sent-count, "    |"  into output-line.
write output-line after advancing 1 line.

if word-count is equal to spaces
  move " | no words were found                         _DELIM_" to num-words.
string num-words delimited by delim, word-count, "    |"  into output-line.
write output-line after advancing 1 line.

if char-count is equal to spaces
  move " | no characters were found                    _DELIM_" to num-chars.
string num-chars delimited by delim, char-count, "    |"  into output-line.
write output-line after advancing 1 line.

if numS-count is equal to spaces
  move " | no numberic strings were found              _DELIM_" to num-numSs.
string num-numSs delimited by delim, numS-count, "    |"  into output-line.
write output-line after advancing 1 line.

if numC-count is equal to spaces
  move " | no numeric characters were found            _DELIM_" to num-numCs.
string num-numCs delimited by delim, numC-count, "    |"  into output-line.
write output-line after advancing 1 line.

if avg-word-sent is equal to "         .00"
  move " | cannot math average words/sentence(*)                    |" to output-line
else
  string words-sent delimited by delim, avg-word-sent, " |" into output-line.
write output-line after advancing 1 line.

if avg-char-word is equal to "         .00"
  move " | cannot math average characters/word(**)                  |" to output-line
else
  string chars-word delimited by delim, avg-char-word, " |" into output-line.
write output-line after advancing 1 line.

write output-line from bar3 after advancing 1 line.


*> print error messages (if any) -----------------------------------------------

move spaces to output-line.
write output-line after advancing 1 line.

if avg-word-sent is equal to "         .00"
  if sent-count is equal to spaces
    move "   * no sentences were found, cannot divide by zero." to output-line
    write output-line after advancing 1 line
  else if word-count is equal to spaces
    move "   * no words were found, average is 0." to output-line
    write output-line after advancing 1 line
  end-if
end-if.

if avg-char-word is equal to "         .00"
  move spaces to output-line
  if word-count is equal to spaces
    move "   ** no words were found, cannot divide by zero." to output-line
    write output-line after advancing 1 line
  else if char-count is equal to "         "
    move "   ** no characters were found, average is 0." to output-line
    write output-line after advancing 1 line
  end-if
end-if.


*> close files & die -----------------------------------------------------------

close input-file, output-file.
stop run.