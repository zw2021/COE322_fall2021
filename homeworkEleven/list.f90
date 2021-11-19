!****************************************************************
!***
!*** This file belongs with the course
!*** Introduction to Scientific Programming in C++/Fortran2003
!*** copyright 2017-2021 Victor Eijkhout eijkhout@tacc.utexas.edu
!***
!*** listf.F90 : linked list basics in Fortran
!***
!****************************************************************
! AUTHORS
! zoelle wong, zfw65
! nick delurgio, npd429
! pavan shukla, pas3488

Program LinkedList

    implicit none

    type node
        integer :: value
        type(node),pointer :: next
    end type node

    type list
        type(node),pointer :: head
    end type list

    ! parameters
    type(list) :: the_list
    type(node),pointer :: node_ptr
    integer :: data
    nullify(the_list%head)
    read(*,*) data
    !call insert(the_list, 1)
    !call insert(the_list, 5)
    !call insert(the_list, 3)
    !call insert(the_list, 2)
    !call print(the_list)
    do while(data>0)
        call insert(the_list, data)
        call print(the_list)
        read(*,*) data
    end do
    call print(the_list)
contains

    subroutine insert( the_list, val )
        implicit none
        ! parameters
        type(list),intent(inout) :: the_list
        integer :: val
        ! local
        type(node),pointer :: current,previous, new_node
        allocate(new_node);  new_node%value = val

        if (.not.associated(the_list%head)) then
            nullify(new_node%next)
            the_list%head => new_node
        else
            current => the_list%head
            do while(associated(current%next) .and. (current%next%value .le. new_node%value) )
                current => current%next
            end do
            nullify(new_node%next)
            new_node%next => current%next
            current%next => new_node
        end if
    end subroutine insert

    integer function length( the_list )
        implicit none
        type(list),intent(in) :: the_list
        ! local
        type(node),pointer :: current

        if (.not.associated(the_list%head)) then
            length = 0
        else
            current => the_list%head
            do
                length = length+1
                if (.not.associated(current%next)) exit
                current => current%next
            end do
        end if
    end function length

    subroutine print(the_list)
        implicit none
        type(list),intent(in) :: the_list
        type(node),pointer :: current

        write(*,'("List: [ ")',advance="no")
        if (associated(the_list%head)) then
            current => the_list%head
            do while (associated(current))
                write(*,'(i1",")',advance="no") current%value
                if (.not.associated(current%next)) exit
                current => current%next
            end do
        end if
        write(*,'(x"]")')

    end subroutine print

end Program LinkedList






