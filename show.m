function [] = show(input, range, zero, MH, ML, ML_2, Z0, Z1, left, right, nleft, nright, rleft, rright)
    figure();
    subplot(3,1,1);
    plot(input);
    hold on;
    plot([1 1] * rleft, ylim, '-p');
    plot([1 1] * rright, ylim, '-p');
    hold off;
    title('input');

    subplot(3,1,2);
    plot(range);
    hold on;
    plot(xlim, [1 1]*MH, '-r');
    plot(xlim, [1 1]*ML, '-r');
    plot(xlim, [1 1]*ML_2, '-b');
    plot([1 1] * left, ylim, '-p');
    plot([1 1] * right, ylim, '-p');
    hold off;
    title('range');

    subplot(3,1,3);
    plot(zero);
    hold on;
    plot(xlim, [1 1]*Z0, '-r');
    plot(xlim, [1 1]*Z1, '-r');
    plot([1 1] * nleft, ylim, '-p');
    plot([1 1] * nright, ylim, '-p');
    hold off;
    title('zero');
end