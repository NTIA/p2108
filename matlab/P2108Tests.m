% copy test .csv files
copyfile ../AeronauticalStatisticalModelTestData.csv

% load example data
aeronauticalStatisticalTestData = readmatrix("AeronauticalStatisticalModelTestData.csv");

% AeronauticalStatisticalModel() tests
for i = 1:size(aeronauticalStatisticalTestData,1)
    % load data
    f__ghz = aeronauticalStatisticalTestData(i,1);
    theta__deg = aeronauticalStatisticalTestData(i,2);
    p = aeronauticalStatisticalTestData(i,3);
    rtn = aeronauticalStatisticalTestData(i,4);
    L_ces__db = aeronauticalStatisticalTestData(i,5);

    % call AeronauticalStatisticalModel()
    [r, L__db] = P2108('AeronauticalStatisticalModel', ...
        f__ghz, theta__deg, p);

    % check results
    assert(r == rtn);
    assert(abs(L__db - L_ces__db) < 0.1);
end
