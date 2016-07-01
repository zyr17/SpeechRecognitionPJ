
dctnum = 16;

parfor i=1:31
    outpath = ID(i);
    outpath = outpath{1};
    outpath = strcat('00000000000/', outpath, '.txt');
    fprintf('text file name: %s\n', outpath)
    fid = fopen(outpath, 'w');
    for j=1:20
        fprintf('%d: doing word No %d\n', i, j);
        for k=1:20
            path1 = filepath(i, j, k);
            path2 = filepath(i, j, k, 32);
            try
                answer = endpoint_detection(path1);
                wavwrite(answer, path2);
                [~, answer2] = MFCC(path2, dctnum);
                fprintf(fid, '    %d %d\n', j, k, size(answer2));
                [s1 s2] = size(answer2);
                for l = 1:s1
                    for p = 1:s2
                        fprintf(fid, '%.15f ', answer2(l, p));
                    end;
                    fprintf(fid, '\n');
                end;
            catch exception
                fprintf('%d %d %d failed\n', i, j, k);
            end;
        end;
    end;
    fclose(fid);
end;
                