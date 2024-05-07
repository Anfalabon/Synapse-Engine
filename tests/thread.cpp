#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <array>
#include <vector>
#include <algorithm>




std::size_t sumEvenSin(const std::size_t start, const std::size_t end)
{
    std::size_t sum = 0;
    for(std::size_t i=start; i<=end; ++i)
    {
        if(i%2 != 0)
        {
            sum += sin(i);
            //sum += i;
        }
    }
    return sum;
}


std::size_t sumOddSin(const std::size_t start, const std::size_t end)
{
    std::size_t sum = 0;
    for(std::size_t i=start; i<=end; ++i)
    {
        if(i%2 != 0)
        {
            sum += sin(i);
            //sum += i;
        }
    }
    return sum;
}


int main()
{
    std::size_t range = 900000000;
    auto start =std::chrono::high_resolution_clock::now();


//    sumEvenSin(range);
//    sumOddSin(range);

//    std::thread firstThread(sumEvenSin, 0, range/2);
//    std::thread secondThread(sumEvenSin, range/2, range);
//    std::thread thirdThread(sumOddSin, 0, range/2);
//    std::thread fourthThread(sumOddSin, range/2, range);
//
//    firstThread.join();
//    secondThread.join();
//    thirdThread.join();
//    fourthThread.join();


//    std::thread t1(sumEvenSin, 0, range/4);
//    std::thread t2(sumEvenSin, range/4, range/2);
//    std::thread t3(sumEvenSin, range/2, (3*range)/4);
//    std::thread t4(sumEvenSin, (3*range)/4 , range);
//
//    std::thread t5(sumOddSin, 0, range/4);
//    std::thread t6(sumOddSin, range/4, range/2);
//    std::thread t7(sumOddSin, range/2, (3*range)/4);
//    std::thread t8(sumOddSin, (3*range)/4 , range);
//
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
//
//    t5.join();
//    t6.join();
//    t7.join();
//    t8.join();




//    std::thread t1(sumEvenSin, 0, range/8);
//    std::thread t2(sumEvenSin, range/8, range/4);
//    std::thread t3(sumEvenSin, range/4, (3*range)/8);
//    std::thread t4(sumEvenSin, (3*range)/8, range/2);
//    std::thread t5(sumEvenSin, range/2, (5*range)/8);
//    std::thread t6(sumEvenSin, (5*range)/8, (3*range)/4);
//    std::thread t7(sumEvenSin, (3*range)/4, (7*range)/8);
//    std::thread t8(sumEvenSin, (7*range)/8, range);
//
//    std::thread t9(sumOddSin, 0, range/8);
//    std::thread t10(sumOddSin, range/8, range/4);
//    std::thread t11(sumOddSin, range/4, (3*range)/8);
//    std::thread t12(sumOddSin, (3*range)/8, range/2);
//    std::thread t13(sumOddSin, range/2, (5*range)/8);
//    std::thread t14(sumOddSin, (5*range)/8, (3*range)/4);
//    std::thread t15(sumOddSin, (3*range)/4, (7*range)/8);
//    std::thread t16(sumOddSin, (7*range)/8, range);
//
//
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
//    t5.join();
//    t6.join();
//    t7.join();
//    t8.join();
//
//    t9.join();
//    t10.join();
//    t11.join();
//    t12.join();
//    t13.join();
//    t14.join();
//    t15.join();
//    t16.join();


//    std::thread t1(sumEvenSin, 0, range/16);
//    std::thread t2(sumEvenSin, range/16, range/8);
//    std::thread t3(sumEvenSin, range/8, 3*range/16);
//    std::thread t4(sumEvenSin, 3*range/16, range/4);
//    std::thread t5(sumEvenSin, range/4, 5*range/16);
//    std::thread t6(sumEvenSin, 5*range/16, 3*range/8);
//    std::thread t7(sumEvenSin, 3*range/8, 7*range/16);
//    std::thread t8(sumEvenSin, 7*range/16, range/2);
//    std::thread t9(sumEvenSin, range/2, 9*range/16);
//    std::thread t10(sumEvenSin, 9*range/16, 5*range/8);
//    std::thread t11(sumEvenSin, 5*range/8, 11*range/16);
//    std::thread t12(sumEvenSin, 11*range/16, 3*range/4);
//    std::thread t13(sumEvenSin, 3*range/4, 13*range/16);
//    std::thread t14(sumEvenSin, 13*range/16, 7*range/8);
//    std::thread t15(sumEvenSin, 7*range/8, 15*range/16);
//    std::thread t16(sumEvenSin, 15*range/16, range);
//
//    // Create threads for sumOddSin function
//    std::thread t17(sumOddSin, 0, range/16);
//    std::thread t18(sumOddSin, range/16, range/8);
//    std::thread t19(sumOddSin, range/8, 3*range/16);
//    std::thread t20(sumOddSin, 3*range/16, range/4);
//    std::thread t21(sumOddSin, range/4, 5*range/16);
//    std::thread t22(sumOddSin, 5*range/16, 3*range/8);
//    std::thread t23(sumOddSin, 3*range/8, 7*range/16);
//    std::thread t24(sumOddSin, 7*range/16, range/2);
//    std::thread t25(sumOddSin, range/2, 9*range/16);
//    std::thread t26(sumOddSin, 9*range/16, 5*range/8);
//    std::thread t27(sumOddSin, 5*range/8, 11*range/16);
//    std::thread t28(sumOddSin, 11*range/16, 3*range/4);
//    std::thread t29(sumOddSin, 3*range/4, 13*range/16);
//    std::thread t30(sumOddSin, 13*range/16, 7*range/8);
//    std::thread t31(sumOddSin, 7*range/8, 15*range/16);
//    std::thread t32(sumOddSin, 15*range/16, range);
//
//    // Join all threads
//    t1.join(); t2.join(); t3.join(); t4.join(); t5.join(); t6.join(); t7.join(); t8.join();
//    t9.join(); t10.join(); t11.join(); t12.join(); t13.join(); t14.join(); t15.join(); t16.join();
//    t17.join(); t18.join(); t19.join(); t20.join(); t21.join(); t22.join(); t23.join(); t24.join();
//    t25.join(); t26.join(); t27.join(); t28.join(); t29.join(); t30.join(); t31.join(); t32.join();


//
//
//    // Create threads for sumEvenSin function
//    std::thread t1(sumEvenSin, 0, range/64);
//    std::thread t2(sumEvenSin, range/64, range/32);
//    std::thread t3(sumEvenSin, range/32, 3*range/64);
//    std::thread t4(sumEvenSin, 3*range/64, range/16);
//    std::thread t5(sumEvenSin, range/16, 5*range/64);
//    std::thread t6(sumEvenSin, 5*range/64, 3*range/32);
//    std::thread t7(sumEvenSin, 3*range/32, 7*range/64);
//    std::thread t8(sumEvenSin, 7*range/64, range/8);
//    std::thread t9(sumEvenSin, range/8, 9*range/64);
//    std::thread t10(sumEvenSin, 9*range/64, 5*range/32);
//    std::thread t11(sumEvenSin, 5*range/32, 11*range/64);
//    std::thread t12(sumEvenSin, 11*range/64, 3*range/16);
//    std::thread t13(sumEvenSin, 3*range/16, 13*range/64);
//    std::thread t14(sumEvenSin, 13*range/64, 7*range/32);
//    std::thread t15(sumEvenSin, 7*range/32, 15*range/64);
//    std::thread t16(sumEvenSin, 15*range/64, range/4);
//    std::thread t17(sumEvenSin, range/4, 17*range/64);
//    std::thread t18(sumEvenSin, 17*range/64, 9*range/32);
//    std::thread t19(sumEvenSin, 9*range/32, 19*range/64);
//    std::thread t20(sumEvenSin, 19*range/64, 5*range/16);
//    std::thread t21(sumEvenSin, 5*range/16, 21*range/64);
//    std::thread t22(sumEvenSin, 21*range/64, 11*range/16);
//    std::thread t23(sumEvenSin, 11*range/16, 23*range/64);
//    std::thread t24(sumEvenSin, 23*range/64, 3*range/8);
//    std::thread t25(sumEvenSin, 3*range/8, 25*range/64);
//    std::thread t26(sumEvenSin, 25*range/64, 13*range/16);
//    std::thread t27(sumEvenSin, 13*range/16, 27*range/64);
//    std::thread t28(sumEvenSin, 27*range/64, 7*range/8);
//    std::thread t29(sumEvenSin, 7*range/8, 29*range/64);
//    std::thread t30(sumEvenSin, 29*range/64, 15*range/16);
//    std::thread t31(sumEvenSin, 15*range/16, 31*range/64);
//    std::thread t32(sumEvenSin, 31*range/64, range);
//
//    // Create threads for sumOddSin function
//    std::thread t33(sumOddSin, 0, range/64);
//    std::thread t34(sumOddSin, range/64, range/32);
//    std::thread t35(sumOddSin, range/32, 3*range/64);
//    std::thread t36(sumOddSin, 3*range/64, range/16);
//    std::thread t37(sumOddSin, range/16, 5*range/64);
//    std::thread t38(sumOddSin, 5*range/64, 3*range/32);
//    std::thread t39(sumOddSin, 3*range/32, 7*range/64);
//    std::thread t40(sumOddSin, 7*range/64, range/8);
//    std::thread t41(sumOddSin, range/8, 9*range/64);
//    std::thread t42(sumOddSin, 9*range/64, 5*range/32);
//    std::thread t43(sumOddSin, 5*range/32, 11*range/64);
//    std::thread t44(sumOddSin, 11*range/64, 3*range/16);
//    std::thread t45(sumOddSin, 3*range/16, 13*range/64);
//    std::thread t46(sumOddSin, 13*range/64, 7*range/32);
//    std::thread t47(sumOddSin, 7*range/32, 15*range/64);
//    std::thread t48(sumOddSin, 15*range/64, range/4);
//    std::thread t49(sumOddSin, range/4, 17*range/64);
//    std::thread t50(sumOddSin, 17*range/64, 9*range/32);
//    std::thread t51(sumOddSin, 9*range/32, 19*range/64);
//    std::thread t52(sumOddSin, 19*range/64, 5*range/16);
//    std::thread t53(sumOddSin, 5*range/16, 21*range/64);
//    std::thread t54(sumOddSin, 21*range/64, 11*range/16);
//    std::thread t55(sumOddSin, 11*range/16, 23*range/64);
//    std::thread t56(sumOddSin, 23*range/64, 3*range/8);
//    std::thread t57(sumOddSin, 3*range/8, 25*range/64);
//    std::thread t58(sumOddSin, 25*range/64, 13*range/16);
//    std::thread t59(sumOddSin, 13*range/16, 27*range/64);
//    std::thread t60(sumOddSin, 27*range/64, 7*range/8);
//    std::thread t61(sumOddSin, 7*range/8, 29*range/64);
//    std::thread t62(sumOddSin, 29*range/64, 15*range/16);
//    std::thread t63(sumOddSin, 15*range/16, 31*range/64);
//    std::thread t64(sumOddSin, 31*range/64, range);
//
//    // Join all threads
//    t1.join(); t2.join(); t3.join(); t4.join(); t5.join(); t6.join(); t7.join(); t8.join();
//    t9.join(); t10.join(); t11.join(); t12.join(); t13.join(); t14.join(); t15.join(); t16.join();
//    t17.join(); t18.join(); t19.join(); t20.join(); t21.join(); t22.join(); t23.join(); t24.join();
//    t25.join(); t26.join(); t27.join(); t28.join(); t29.join(); t30.join(); t31.join(); t32.join();
//    t33.join(); t34.join(); t35.join(); t36.join(); t37.join(); t38.join(); t39.join(); t40.join();
//    t41.join(); t42.join(); t43.join(); t44.join(); t45.join(); t46.join(); t47.join(); t48.join();
//    t49.join(); t50.join(); t51.join(); t52.join(); t53.join(); t54.join(); t55.join(); t56.join();
//    t57.join(); t58.join(); t59.join(); t60.join(); t61.join(); t62.join(); t63.join(); t64.join();
//



























    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;


    std::cout << "Execution time: " << duration.count() << " seconds." << '\n';

    return 0;
}
