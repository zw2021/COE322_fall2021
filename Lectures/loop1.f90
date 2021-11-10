program loop1
    integer :: n
    integer :: divisor
    logical :: isprime = .true.

    read *, n

    do i=2,n/2
        if(mod(n,i) == 0) then
            isprime = .false.
            divisor = i
            exit
        end if
    end do

    if(isprime) then
        print *,"Is prime"
    else
        print *,"Is not prime, divisible by",divisor
    end if





end program loop1