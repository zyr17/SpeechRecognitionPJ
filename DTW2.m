function [answer] = DTW2(a, b)
    [n, ~] = size(a);
    [m, ~] = size(b);
    if n > m
        tmp = n;
        n = m;
        m = tmp;
        tmp = a;
        a = b;
        b = tmp;
    end;
    if n == 0
        answer = 99999;
        return;
    end;
    d = zeros(n + 1, m + 1);
    d2 = zeros(n + 1, m + 1);
    
    %fa = zeros(n + 1, m + 1);
    
    for i = 1:n + 1
        for j = 1:m + 1
            d(i, j) = 99999;
            d2(i, j) = 1;
        end;
    end;
    d(1, 1) = 0;
    d2(1, 1) = 0;
    answer = 99999;
    for i = 1:n
        for j = 1:m
            tdis = abs(a(i) - b(j));
            if (d(i, j) + tdis * 2) * d2(i + 1, j + 1) < d(i + 1, j + 1) * (d2(i, j) + 2)
                d(i + 1, j + 1) = d(i, j) + tdis * 2;
                d2(i + 1, j + 1) = d2(i, j) + 2;
                
                %fa(i + 1, j + 1) = 1;
                
            end;
            if (d(i + 1, j) + tdis) * d2(i + 1, j + 1) < d(i + 1, j + 1) * (d2(i + 1, j) + 1)
                d(i + 1, j + 1) = d(i + 1, j) + tdis;
                d2(i + 1, j + 1) = d2(i + 1, j) + 1;
                
                %fa(i + 1, j + 1) = 2;
                
            end;
            if (d(i, j + 1) + tdis) * d2(i + 1, j + 1) < d(i + 1, j + 1) * (d2(i, j + 1) + 1) && m - j > n - i
                d(i + 1, j + 1) = d(i, j + 1) + tdis;
                d2(i + 1, j + 1) = d2(i, j + 1) + 1;
                
                %fa(i + 1, j + 1) = 3;
                
            end;
            if i == 1 && j + n < m + 2
                if tdis * d2(i + 1, j + 1) < d(i + 1, j + 1)
                    d(i + 1, j + 1) = tdis * 2;
                    d2(i + 1, j + 1) = 2;
                end;
            end;
            if i == n && d2(i + 1, j + 1) ~= 0
                if answer > d(i + 1, j + 1) / d2(i + 1, j + 1)
                    answer = d(i + 1, j + 1) / d2(i + 1, j + 1);
                    
                    %endx = i + 1;
                    %endy = j + 1;
                    
                end;
            end;
        end;
    end;
    %{
    while (1 == 1)
        fprintf('%d %d %f\n', endx - 1, endy - 1, abs(a(endx) - b(endy)));
        if fa(endx, endy) == 1
            endx = endx - 1;
            endy = endy - 1;
        else if fa(endx, endy) == 2
                endy = endy - 1;
            else if fa(endx, endy) == 3
                    endx = endx - 1;
                else break;
                end;
            end;
        end;
    end;
    %}
end