for i = 7:13
    for j = 1:60
        try
        name = strcat(IDD(i), '_', good(j), '.wav');
        name = name{1};
        file1 = strcat('00000000000\', name);
        %file1 = file1{1};
        file2 = strcat('00000000000\',file1);
        %file2 = file2{1};
        input = wavread(file1);
        wavwrite(input, file2);
        fprintf('%d %s\n', i, name);
        sound(input);
        %pause(2);
        catch
            fprintf('%d %d baozha\n',i,j);
        end;
    end;
end;