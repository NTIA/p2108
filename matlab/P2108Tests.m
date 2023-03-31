% copy test .csv files
copyfile ../AeronauticalStatisticalModelTestData.csv
copyfile ../HeightGainTerminalCorrectionModelTestData.csv
copyfile ../TerrestrialStatisticalModelTestData.csv

% load example data
aeronauticalStatisticalTestData = readmatrix("AeronauticalStatisticalModelTestData.csv");
heightGainTerminalCorrectionTestData = readmatrix("HeightGainTerminalCorrectionModelTestData.csv");
terrestrialStatisticalTestData = readmatrix("TerrestrialStatisticalModelTestData.csv");

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


% HeightGainTerminalModel() tests
for i = 1:size(heightGainTerminalCorrectionTestData,1)
    % load data
    f__ghz = heightGainTerminalCorrectionTestData(i,1);
    h__meter = heightGainTerminalCorrectionTestData(i,2);
    w_s__meter = heightGainTerminalCorrectionTestData(i,3);
    R__meter = heightGainTerminalCorrectionTestData(i,4);
    clutter_type = heightGainTerminalCorrectionTestData(i,5);
    rtn = heightGainTerminalCorrectionTestData(i,6);
    A_h__db = heightGainTerminalCorrectionTestData(i,7);

    % call model
    [r, A__db] = P2108('HeightGainTerminalCorrectionModel', f__ghz, ...
        h__meter, w_s__meter, R__meter, clutter_type);

    % check results
    assert(r == rtn);
    assert(abs(A__db - A_h__db) < 0.1);
end

% TerrestrialStatisticalModel() tests
for i = 1:size(terrestrialStatisticalTestData,1)
    % load data
    f__ghz = terrestrialStatisticalTestData(i,1);
    d__km = terrestrialStatisticalTestData(i,2);
    p = terrestrialStatisticalTestData(i,3);
    rtn = terrestrialStatisticalTestData(i,4);
    L_ctt__db = terrestrialStatisticalTestData(i,5);

    % call model
    [r, L__db] = P2108('TerrestrialStatisticalModel', f__ghz, d__km, p);

    % check results
    assert(r == rtn);
    assert(abs(L__db - L_ctt__db) < 0.1);
end