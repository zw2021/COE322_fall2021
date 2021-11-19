!****************************************************************
!****
!**** This file belongs with the course
!**** Introduction to Scientific Programming in C++/Fortran2003
!**** copyright 2017-9 Victor Eijkhout eijkhout@tacc.utexas.edu
!****
!**** pointexample.F90 : example for the textbook exercise
!****
!****************************************************************

Module PointClass
    Type,public :: Point
        real(8) :: x,y
    contains
        procedure, public :: &
                distance, sum
    End type Point
contains
    !! ... distance function ...
    real(8) function distance(me,other)
        implicit none
        class(Point) :: me
        type(Point),intent(in) :: other
        real(8) :: dx,dy
        dx = me%x-other%x; dy = me%y-other%y
        distance = sqrt( dx**2 + dy**2 )
    end function distance

    !! ... add function ...
    Type(Point) function add(me, other)
        implicit none
        class(Point) :: me
        type(Point),intent(in) :: other
        return Point(me%x + other%x, p%y + other%y)

    end function add

End Module PointClass


Program PointTest
    use PointClass
    implicit none
    type(Point) :: p1,p2

    p1 = point(1.d0,1.d0)
    p2 = point(4.d0,5.d0)

    print *,"Distance:",&
            p1%distance(p2)

End Program PointTest

