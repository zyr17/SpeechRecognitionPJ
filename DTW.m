function [answer] = DTW(a, b)

    %answer = DTW2(a, b);
    %return;
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
        answer = 999;
        return;
    end;
    d = zeros(n + 1, m + 1);
    for i = 1:n + 1
        for j = 1:m + 1
            d(i, j) = 999;
        end;
    end;
    d(1, 1) = 0;
    www = 5;
    www=max(www, abs(n-m));
    for i = 1:n
        ii = round(i * m / n);
        for j = max(ii - www, 1):min(ii + www, m)
            tdis = norm(a(i,:) - b(j,:));
            tmp = min(d(i, j) + tdis * 2, min(d(i, j + 1) + tdis, d(i + 1, j) + tdis));
            if d(i + 1, j + 1) > tmp
                d(i + 1, j + 1) = tmp;
            end;
        end;
    end;
    answer = d(n + 1, m + 1) / (n + m);
end