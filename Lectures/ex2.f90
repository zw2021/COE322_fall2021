program ex2

integer(8) :: i
read *,i

if(mod(i,3) == 0 .and. mod(i,5) == 0) then
print *,"Fizzbuzz!"
else if(mod(i,3) == 0) then
print *,"Fizz!"
else if (mod(i,5) == 0) then
print *,"Buzz!"
end if

end program ex2
