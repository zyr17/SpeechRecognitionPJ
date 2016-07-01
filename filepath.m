function [answer] = filepath(IDNum, WordsNum, num, varargin)
    if nargin < 3
        error(message('error in filepath'));
    end;
    if nargin < 4
        folder = IDNum;
    end;
    if nargin == 4
        folder = varargin{1};
    end;
    tmp = strcat(ID(folder), '/', ID(IDNum), '_', Words(WordsNum), '_', FileNums(num), '.wav');
    answer = tmp{1};
end