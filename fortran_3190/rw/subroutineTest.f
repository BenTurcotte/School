! first attempt at subroutines
        program main
        implicit none
        integer :: x,y
        real, dimension(2) :: r
        character :: c
        character(len=20) :: str

! example of user type
        type structure
            integer :: i
            character, dimension(10) :: charArr
            character(len=10) :: str
            real :: m
        end type structure

        type (structure) :: mystruct
        mystruct%i = 14
        mystruct%str = "a string."
        mystruct%charArr = "a charArr"
        mystruct%m = .801
        write(*,*) mystruct%i,mystruct%str,mystruct%charArr,mystruct%m

! calling a couple subroutines
        call sayHi()
        call init(r, str)
        write(*,*) r,' ', str

! call subroutine that prints a box with boarders of a given character
        write(*,*) 'give dimensions of box (x,y)'
        read(*,*) x,y
        write(*,*) 'give character for box'
        read(*,*) c
        call print_box(x,y,c)

        end program main

! ----------------------------------------------------------------------
        subroutine sayHi()
        write(*,*) 'Hi!'
        return
        end subroutine

! ----------------------------------------------------------------------
        subroutine init(r, str)
        real, intent(inout), dimension(2) :: r
        character(len=20), intent(inout)  :: str
        r = (/3.141, 2.718/)
        str = 'success.'
        return
        end subroutine init

! ----------------------------------------------------------------------
        subroutine print_box(x,y,c)
            character, dimension(100,100) :: m
            integer, intent(in) :: x,y
            integer :: i,j
            character, intent(in) :: c
            m = ' '
            if (x > 100 .OR. y > 100) then
                write(*,*) 'too big. cannot print'
            else
                m(:x,1) = c
                m(1,:y) = c
                m(:x,y) = c
                m(x,:y) = c

                do i = 1,x
                    write(*,*) m(i,:y)
                end do
            end if

            return
        end subroutine print_box

! ----------------------------------------------------------------------