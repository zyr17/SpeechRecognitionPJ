warning('off','all')
addpath('D:\octave\toolbox\voicebox');
FS = 8000;
nBits = 16;
Time = 2;
recObj = audiorecorder(FS, nBits, 1);
disp('-----------------');
disp('Start speaking');
recordblocking(recObj, Time);
disp('End of Recording.');
disp('-----------------');

myRecording = getaudiodata(recObj);

filename = 'testdata.wav';
filename2 = 'testdata-cut.wav';
wavwrite(myRecording, FS, filename);
answer = endpoint_detection(filename);
wavwrite(answer, filename2);
dctnum = 16;
[~, answer2] = MFCC(filename2, dctnum);
fid = fopen('testdata.txt', 'w');
fprintf(fid, '    %d %d\n', size(answer2));
[s1 s2] = size(answer2);
for l = 1:s1
    for p = 1:s2
        fprintf(fid, '%.15f ', answer2(l, p));
    end;
    fprintf(fid, '\n');
end;