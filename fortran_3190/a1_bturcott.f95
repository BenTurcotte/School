!     Game of Hangman by Dave Ahl, digital
!     Based on a basic program written by Ken Aupperle
!       Half Hallow Hills H.S. Dix Hills NY
!     Converted to Fortran 77 by M.Wirth, April 2012
!     Converted to Fortran 95 by Ben Turcotte, January 2016
program hangman
implicit none
real :: rnd
integer :: randindex, foundflag, usedFlag, needNewWord
integer :: i, j
integer :: actualwordlen, usedwordcount, wrongguesscount, letterguesscount
integer, dimension(50) :: wordusestatus
character :: inputchar, playagain
character(len=30) :: inputStr
character(len=20) :: actualword, displayword
character, dimension(52) :: usedletters
character(len=12), dimension(12) :: person
character(len=20), dimension(50) :: wordbank

wordbank(1:7) = (/"gum","sin","for","cry","lug","bye","fly"/)
wordbank(8:14) = (/"ugly","each","from","work","talk","with","self"/)
wordbank(15:21) = (/"pizza","thing","feign","fiend","elbow","dirty","fault"/)
wordbank(22:28) = (/"budget","spirit","quaint","maiden","escort","pickax","kidney"/)
wordbank(29:33) = (/"example","tension","quinine","replica","sleeper"/)
wordbank(34:38) = (/"triangle","kangaroo","mahogany","sergeant","sequence"/)
wordbank(39:43) = (/"moustache","dangerous","scientist","different","quiescent"/)
wordbank(44:45) = (/"magistrate","phytotoxic"/)
wordbank(46:48) = (/"erroneously","loudspeaker","matrimonial"/)
wordbank(49) = "thigmotropism"
wordbank(50) = "parasympathomimetic"

write (*,*) 'the game of hangman'
usedwordcount = 0
wordusestatus = 0

!  this is the game loop
do
    ! reset all reused vars
    wrongguesscount = 0
    letterguesscount = 0
    displayword = ''
    usedletters = ''
    call update_person(0, person)
    
    ! randomly select unused word for this round
    randindex = 0
    do
        ! rnd = rand <-- this line produces "Error: Function ‘rand’ at (1) has no IMPLICIT type"
        randindex = randindex +1
        if(wordusestatus(randindex) == 0) exit
    end do
    wordusestatus(randindex) = 1
    usedwordcount = usedwordcount +1
    actualword = wordBank(randindex)

    forall(i=1:20, displayword(i:i) /= ' ')
        displayword(i:i) = ' '
    end forall
    forall(i=1:len(trim(actualword)), displayword(i:i) /= "-")
        displayword(i:i) = '-'
    end forall

    ! this is the inner loop for each word
    do
        inputchar = ' '
        write(*,*) displayword
        write(*,*) 'Here are the letters you used:'
        write(*,*) usedletters
        write(*,*) 'What is your guess?'
        read(*,*) inputchar

        usedFlag = 0
        do i=1,letterguesscount
            if(usedletters(i) == inputchar) then
                write(*,*) 'You already guessed that letter'
                usedFlag = 1
            end if
        end do
        if(usedFlag == 1) cycle

        if(usedFlag == 0) then
            letterguesscount = letterguesscount +1
            usedletters((letterguesscount*2)-1) = inputchar
            usedletters(letterguesscount*2) = ','
        end if

        ! update the display word
        foundflag = 0
        do i=1,len(actualword)
            if (actualword(i:i) == inputchar) then
                displayword(i:i) = inputchar
                foundflag = 1
            end if
        end do

        ! user won this round
        if (displayword == actualword) then
            write(*,*) 'You found the word'
            exit
        end if

        if(foundflag == 1) then
            write(*,*) displayword
            write (*,*) 'What is your guess for the word?'
            read(*,*) inputStr
            if(inputStr == actualword) then
                write (*,*) 'Right! It took you',letterguesscount,'guesses'
                exit
            end if
        else
            write (*,*) 'Sorry, that letter is not in the word'
            wrongguesscount = wrongguesscount +1
            call update_person(wrongguesscount, person)
            call update_message(wrongguesscount, person)
        end if
    end do

    if (usedwordcount == 50) then
        write(*,*) 'You did all the words'
        exit
    end if

    playagain = ' '
    write(*,*) 'Play again? (y/n)'
    read(*,*) playagain

    if(playagain /= 'y' .AND. playagain /= 'Y') exit
end do

write(*,*) 'Its been fun. bye for now.'
write(*,*) 'Exiting...'

end program hangman

! -----------------------------------------------------------------------------
subroutine update_person(i,person)
integer, intent(in) :: i
character(len=12), dimension(12), intent(inout) :: person
write(*,*) 'called update_person'
select case (i)
    case(0)
        person(1)    = ' XXXXXXX'
        person(2)    = ' X     X'
        person(3:12) = ' X'
    case(1)
        person(3) = ' X    ---'
        person(4) = ' X   (. .)'
        person(5) = ' X    ---'
    case(2)
        person(6:9) = ' X     X'
    case(3)
        person(4) = ' X \ (. .)'
        person(5) = ' X  \ ---'
        person(6) = ' X   \ X'
        person(7) = ' X    \X'
    case(4)
        person(4) = ' X \ (. .) /'
        person(5) = ' X  \ --- /'
        person(6) = ' X   \ X /'
        person(7) = ' X    \X/'
    case(5)
        person(10) = ' X    /'
        person(11) = ' X   /'
    case(6)
        person(10) = ' X    / \ '
        person(11) = ' X   /   \ '
    case(7)
        person(3) = ' X    ---  \ '
    case(8)
        person(3) = ' X /  ---  \ '
    case(9)
        person(12) = ' X        \-'
    case(10)
        person(12) = ' X -/     \-'
end select
return
end subroutine update_person

! -----------------------------------------------------------------------------        
subroutine update_message(i, person)
character(len=12), dimension(12), intent(inout) :: person
integer, intent(in) :: i
integer :: n
select case(i)
case(1)
    write (*,*) "First we draw a head."
case(2)
    write (*,*) "Now we draw a body."
case(3)
    write (*,*) "Next we draw an arm."
case(4)
    write (*,*) "This time it's the other arm."
case(5)
    write (*,*) "Now, let's draw the right leg."
case(6)
    write (*,*) "This time we draw the left leg."
case(7)
    write (*,*) "Now we put up a hand."
case(8)
    write (*,*) "Next the other hand."
case(9)
    write (*,*) "Now we draw one foot."
case(10)
    write (*,*) "Here's the other foot -- You're hung!!."
end select

do n=1,12
    write(*,*) person(n)
end do

return
end subroutine update_message