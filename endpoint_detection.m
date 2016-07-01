function [answer] = main(filename)

    %读取音频，设置步长，计算短时幅度 短时能量和短时过零率
    %fprintf('%s\n', filename);
    
    %answer = vad_ezm2(filename);
    %return;
    
    [input, Fs, bit] = wavread(filename);
    if size(input) < 16000
        ss = size(input);
        input = [input; zeros(16000 - size(input), 1)];
        for i=ss:16000
            input(i) = input(i - 800);
        end;
    end;
    %input = input / max(input);
    Fs = Fs * 2;
    short_time = 80;
    step = floor(Fs / short_time);
    energy = zeros(step, 1);
    zero = energy;
    range = energy;
    zero_ori = zeros(Fs, 1);
    last = input(1);
    for i = 1:Fs
        if last ~= 0 && input(i) ~= 0 && ((last > 0) == (input(i) < 0))
            zero_ori(i) = 1;
        else
            zero_ori(i) = 0;
        end;
        if (input(i) ~= 0)
            last = input(i);
        end;
    end;
    for i = 1:Fs
        j = floor((i - 1) / short_time) + 1;
        range(j) = range(j) + abs(input(i));
        zero(j) = zero(j) + zero_ori(i);
        energy(j) = energy(j) + input(i) ^ 2;
    end;
    
    % 定义MH ML，通过短时幅度计算第一组范围
    
    MLeft = 0;
    MLC = 0;
    MRight = 0;
    MRC = 0;
    for i = 1:floor(step / 10)
        MLeft = MLeft + range(i);
        MLC = MLC + 1;
    end;
    for i = floor(step * 9 / 10):step
        MRight = MRight + range(i);
        MRC = MRC + 1;
    end;
    MLeft = MLeft / MLC;
    MRight = MRight / MRC;
    if (MLeft > MRight)
        MLeft = MRight;
    end;
    MNoise = MLeft;
    
    MH = (max(range) - MNoise) / 5 + MNoise;
    ML = (MH - MNoise) / 4 + MNoise;
    ML_2 = (ML - MNoise) / 3 + MNoise;
    
    left = step;
    right = 1;
    
    for i = 1:step
        if range(i) > MH
            if i < left
                left = i;
            end;
            right = i;
        end;
    end;
    while (left > 1 && range(left - 1) > ML)
        left = left - 1;
    end;
    while (right < step && range(right + 1) > ML)
        right = right + 1;
    end;
    
    %计算Z0
    ZL = 0;
    ZLC = 0;
    ZR = 0;
    ZRC = 0;
    for i = 1:floor(step / 10)
        ZL = ZL + zero(i);
        ZLC = ZLC + 1;
    end;
    for i = floor(step * 9 / 10):step
        ZR = ZR + zero(i);
        ZRC = ZRC + 1;
    end;
    ZL = ZL / ZLC;
    ZR = ZR / ZRC;
    if (ZR < ZL)
        ZL = ZR;
    end;
    
    Z0 = ZL;
    Z1 = Z0 * 3;
    
    %检查过零率，得到第二组范围
    delta = 220 / 1000 / 2 * step;
    nleft = left;
    nright = right;
    for i = floor(left - delta):left;
        if i < 1
            continue;
        end;
        if zero(i) / Z1 * range(i) / ML_2 > 1 && i < nleft
            nleft = i;
        end;
    end;
    for i = right:floor(right + delta)
        if i > step
            continue;
        end;
        if zero(i) / Z1 * range(i) / ML_2 > 1
            nright = i;
        end;
    end;
    while (nleft > 1 && zero(nleft - 1) / Z1 * range(nleft - 1) / ML_2 > 1)
        nleft = nleft - 1;
    end;
    while (nright < step && zero(nright + 1) / Z1 * range(nright + 1) / ML_2 > 1)
        nright = nright + 1;
    end;
    
    %计算最终范围
    rleft = (nleft - 1) * short_time + 1;
    rright = nright * short_time;
    %fprintf('%d %d %d %d\n',nleft, nright, rleft, rright);
    answer = input(rleft:rright);
    %answer = input;
    
    %show(input, range, zero, MH, ML, ML_2, Z0, Z1, left, right, nleft, nright, rleft, rright);
    
end