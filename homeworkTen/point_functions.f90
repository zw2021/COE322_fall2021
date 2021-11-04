!****************************************************************
!***
!*** This file belongs with the course
!*** Introduction to Scientific Programming in C++/Fortran2003
!*** copyright 2017/8 Victor Eijkhout eijkhout@tacc.utexas.edu
!***
!*** type.F90 : fortran types, definition, use, parameter passing
!***
!****************************************************************

! ok to put the module in same file or one file; module should be listed above
! icpc -c porgram.cpp ".o files only compile the file" - will create an object file + executable
! compile the module, makes a .mod file (which corresponds to a header file); saying use-blah tells the file to look for the .mod file
!
! AUTHORS
! zoelle wong, zfw65
! nick delurgio, npd429
! pavan shukla, pas3488
Program size
    implicit none

    type point
        real :: x,y
    end type point

    type rectangle
        type(point) :: p1,p2
    end type rectangle

    type(point) :: p1,p2
    type(rectangle) :: r1
    real(4) :: x, y
    print *,"Enter First Points in a Single Line (x,y):"
    read (*,*) x, y
    p1 = point(x, y)
    print *, "Enter Second Point in a Single Line (x, y):"
    read (*,*) x, y
    p2 = point(x, y)
    print *, "Area:", area(p2, p1)


contains
    real(4) function length(p)
        implicit none
        type(point),intent(in) :: p
        length = sqrt( &
                p%x**2 + p%y**2 )
    end function length

    real(4) function angle(p)
        implicit none
        type(point),intent(in) :: p
        angle = atan2(&
                p%y/ p%x)
    end function angle
! infectious disease = single person project
    ! chapter 57, 58, 59, 60 = 2 or 3 people BUT MOST BE SUPER CLEAN AND SUPER THORUH
    ! 3 PEOPLE - YES YOU SHOULD HAVE UNIT TESTING???
    ! NOT busy work; just a software engineering tool
    ! amazon project is walked through
    ! 64 - FORTRAN
    real(4) function area(p1, p2)
        implicit none
        real(4) :: l, w

        type(point),intent(in) :: p1
        type(point),intent(in) :: p2
        l = abs(p1%y - p2%y)
        w = abs(p1%x - p2%x)
        area = l*w
        ! fill this out later
    end function area

end Program size
