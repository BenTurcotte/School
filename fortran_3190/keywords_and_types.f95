program keysAndTypes
	
! COMMON TYPES: integer, real, complex, logical, character ====================

! INETEGER -- signed value
	! default size: 2 bytes
	! optional sizes: number_2 (short, 2 bytes, default)
	!     			  number_4 (long, 4 bytes, user specified)
	!
	! maxShort =  327567
	! minShort = -32768
	! maxLong  =  2147483647
	! mixLong  = -2147483648

! REAL -- signed floating point value
	! default size: 4 bytes
	! optional sizes: num_4 (confined to first 7 digits, 4 bytes)
	!				  num_8 (confined to first 15 digits, 8 bytes)
	!
    ! 14.0   -> printed, will output 14.00000
    ! 14.0_8 -> printed, will output 14.0000000000000

! COMPLEX -- given by a pair of real numbers enclosed in parentheses
	! ex. (-23.7,3.141592)

! LOGICAL -- used to indicate truth of an expression (boolean)
	!two legal values: .TRUE.
	!				   .FALSE.

! CHARACTER -- linear sequence of characters (a.k.a. character string)
	! must be enclosed in single quotes ('string') or double quotes ("string")

! END OF COMMON TYPES =========================================================

! INQUIRY FUNCTIONS -- all numeric types have common inquiry functions ========
	integer :: x
	x = 128
	! # of significant digits
	digits(x)
	! almost negligible compared to i
	epsilon(x)
	! largest number
	huge(x)
	! maximum exponent
	maxexponent(x)
	! minimum exponent
	minexponent(x)
	! decimal precision
	precision(x)
	! base
	radix(x)
	! decimal exponent range
	range(x)
	! smallest positive number
	tiny(x)
! END OF INQUIRY FUNCTIONS ====================================================

! VARIABLES ===================================================================

! IDENTIFIERS
	! max length: 31 characters
	! legal chars: letters, digits, underscores
	!
	! NOTE: fortran words are NOT reserved -- "program" could be a variable

! TYPE DECLARATIONS
	! explicit declaration in f77
	integer i
	! explicit declaration in f90/f95
	integer :: i

! TYPE PROPERTIES -- consist of char length & kind
	! KIND works the same for variables as it does for numeric constants
	!   it is related to machine representation
	!   if no kind is specified, the default kind is used
	real(kind=4) :: r1, r2
	real(4) :: r1, r2

	! LEN allows the length of the character to be specified
	!   if len is omitted, a value of i is assumed
	character(len=12) :: string

	! VARIABLE INITIALIZATION
	integer :: a, b
	a=1
	b=2
	! OR
	integer :: a=1, b=2

! VARIABLE ATTRIBUTES
	! DIMENSION is used for arrays
	!   used to specify lower & upper bounds of an array
	integer, dimension(4,4) :: matrix
	
	! PARAMETER is used for named constants -- cannot be reassigned later
	real, parameter :: pi=3.141592

	! variable attributes define restrictions on the effective use of the var.
	! other data attributes include:
	!   allocatable, intent, pointer, save, & target

! IMPLICIT DECLARATIONS
	! if variables are implicitly typed, some assumptions are made:
	!   vars that start with i, j, k, & l are all assumed to be INTEGERs
	!   all others are assumed to be REALs
	!
	! to disable implicit declarations:
	implicit none
	! if implicit declarations are not disabled, the compiler will not catch
	!   misspelled identifiers which could result in unexpected behaviour
! END OF VARIABLES ============================================================

! OPERATORS & EXPRESSIONS =====================================================

end program keysAndTypes