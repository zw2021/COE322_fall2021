module ex3
        type point
                real :: x,y
        end type point
        type Rectangle
                type(Point) :: p1,p2
        end type rectangle
        contains
        real function area(rect)
                implicit none
                type(rectangle), intent(in) :: rect
                real :: dx, dy
                dx = rect%p2%x - rect%p1%x
                dy = rect%p2%y - rect%p1%y
                area = ABS(dx*dy)
        end function area
end module ex3
program hw10
        use ex3
        implicit none
        real :: x1,y1,x2,y2
        type(point) :: p3,p4
        type(rectangle) :: rect1
        read(*,*) x1,y1,x2,y2
        p3 = point(x1,y1)
        p4 = point(x2,y2)
        rect1 = Rectangle(p3,p4)
        print *, area(rect1)
end program hw10





