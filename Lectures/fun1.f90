program fun1
    implicit none
    real(4) :: userinput
    print *, "Type a positive number: "
    userinput = read_positive()
    print *,"Thank you for",userinput
    
    contains
    real(4) function read_positive()
        implicit none
        real(4) :: n
        read *, n
        if(n < 0) then
            print *,"Error, number less than zero"
            return
        else
            read_positive = n
        end if

    end function read_positive

end program fun1