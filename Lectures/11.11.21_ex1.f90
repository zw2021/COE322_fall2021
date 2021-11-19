!****************************************************************
!****
!**** This file belongs with the course
!**** Introduction to Scientific Programming in C++/Fortran2003
!**** copyright 2017-2021 Victor Eijkhout eijkhout@tacc.utexas.edu
!****
!**** scalar.F90 : geometry with operator overloading
!****
!****************************************************************

Module Physics

    Type,public :: VectorField
        real(8) :: value
    contains
        procedure,public :: set,print
        procedure,public :: add, alloc, setlinear
    End type VectorField

    interface operator(+)
        module procedure add
    end interface operator(+)

contains
    subroutine setlinear(v)
        implicit none
        class(VectorField) :: v
        !real(8),intent(in) :: x
        v%value = x

    end subroutine setlinear

    subroutine set(v,x)
        implicit none
        class(VectorField) :: v
        real(8),intent(in) :: x

        v%value = x
    end subroutine set

    subroutine print(v)
        implicit none
        class(VectorField) :: v

        print '(f7.4)', v%value
    end subroutine print

    function add(in1,in2) result(out)
        implicit none
        class(VectorField),intent(in) :: in1
        type(VectorField),intent(in) :: in2
        type(VectorField) :: out

        out%value = in1%value + in2%value
    end function add

End Module Physics

Program Simulation
    use Physics
    implicit none
    integer,parameter :: size = 5

    Type(VectorField) :: u,v,z

    call u%set(2.d0)
    call v%set(1.d0)

    !  z = u%add(v)
    z = u+v
    call z%print()

End Program Simulation

