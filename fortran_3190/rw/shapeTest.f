        program makeperson
            implicit none
            integer :: i, n
            character(len=12), dimension(12) :: person

            do n=0,10
                call update_person(n,person)
                do i=1,12
                    write(*,*) person(i)
                end do
            end do
                
        end program makeperson

        subroutine update_person(i,person)
            integer, intent(in) :: i
            character(len=12), dimension(12), intent(inout) :: person
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
                    person(10) = ' X    / \'
                    person(11) = ' X   /   \'
                case(7)
                    person(3) = ' X    ---  \'
                case(8)
                    person(3) = ' X /  ---  \'
                case(9)
                    person(12) = ' X        \-'
                case(10)
                    person(12) = ' X -/     \-'
            end select
            return
        end subroutine update_person