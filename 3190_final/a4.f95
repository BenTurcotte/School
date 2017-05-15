! Bturcott - 0832217
! Assignment 4 - CIS*3190
! "Sieve of Atkin" - fortran
program a4
implicit none

! var declarations & initialization
integer :: prime_flags(0:2000000)
integer :: lim_sqrt = 0
integer :: lim = 2000000
integer :: check_me
integer :: i
integer(kind=4) :: k
logical :: file_exists
integer :: cant_open

prime_flags(2) = 1
prime_flags(3) = 1

! prompt user for input
do
  write(*,*) 'limit: '
  read(*,*)  lim
  if (lim > 0 .and. lim < 10000001) exit
  write(*,*) 'Error! Number must be between 0 and 10000000.'
end do

! init input-dependent var
lim_sqrt = sqrt(real(lim))

! do maths
do i = 1,lim_sqrt
  do k = 1,lim_sqrt
    check_me = (4 * i * i) + (k * k)
    if (check_me <= lim .and. (mod(check_me,12) == 1 .or. mod(check_me,12) == 5)) then
      prime_flags(check_me) = 1
    end if
    check_me = (3 * i * i) + (k * k)
    if (check_me <= lim .and. mod(check_me,12) == 7) then
      prime_flags(check_me) = 1
    end if
    if (i > k) then
      check_me = (3 * i * i) - (k * k)
      if (check_me <= lim .and. mod(check_me,12) == 11) then
      prime_flags(check_me) = 1
      end if
    end if
  end do
end do

! eliminate multiples of primes
do i = 2,lim
  if (prime_flags(i) == 1) then
    do k = i * i, lim, i
      if (k < 0) exit
      prime_flags(k) = 0
    end do
  end if
end do

! print results
inquire(file="fortran_output.txt", exist = file_exists)
if (file_exists) then
  open(1, file="fortran_output.txt", status = "old", iostat = cant_open)
else
  open(1, file="fortran_output.txt", status = "new", iostat = cant_open)
end if
if (cant_open /= 0) then
  write(*,*) 'Error: could not open output file.'
  call exit(1)
end if
do i = 0,lim
  if (prime_flags(i) == 1) then
    write(1,*) i
  end if
end do
close(1)

! mic drop
end program a4