function tests = dense_lattice_solve_test
tests = functiontests(localfunctions);
end

function testSolveSquare1(testCase)

    m1=5;n1=5;p=2;m2=5;n2=10;
    [C, c_data]=dense_lattice_solve_test_work(m1,n1,m2,n2,p);
    verifyEqual(testCase,C.vals,c_data,'AbsTol',100*eps );
end


function testSolveSquare2(testCase)
    m1=5;n1=5;p=1;m2=5;n2=10;
    [C, c_data]=dense_lattice_solve_test_work(m1,n1,m2,n2,p);
    verifyEqual(testCase,C.vals,c_data,'AbsTol',100*eps);
end

function testSolveLeastSquares1(testCase)
    m1=10;n1=5;p=2;m2=10;n2=10;
    [C, c_data]=dense_lattice_solve_test_work(m1,n1,m2,n2,p);
    verifyEqual(testCase,C.vals,c_data,'AbsTol',100*eps );
end


function testSolveLeastSquares2(testCase)
    m1=10;n1=5;p=1;m2=10;n2=10;
    [C, c_data]=dense_lattice_solve_test_work(m1,n1,m2,n2,p);
    verifyEqual(testCase,C.vals,c_data,'AbsTol',100*eps);
end


