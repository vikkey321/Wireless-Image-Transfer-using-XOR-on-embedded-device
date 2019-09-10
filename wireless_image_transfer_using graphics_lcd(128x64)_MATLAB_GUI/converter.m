clear;
clear all;
clc;
img=imread('C:\01.jpg');

img=imresize(img,[64,128]);
img=rgb2gray(img);
img=im2bw(img);
for i=1:1:64
        for j=1:1:128
            img(i,j)=img(i,j);
        end
end


imshow(img);

s=(0:7);
s=[0 0 0 0 0 0 0 0];
fprintf('{\n');

for i=1:8:64
    fprintf('{');
    for j=1:1:128
        s(8)=img(i,j);
        s(7)=img(i+1,j);
        s(6)=img(i+2,j);
        s(5)=img(i+3,j);
        s(4)=img(i+4,j);
        s(3)=img(i+5,j);
        s(2)=img(i+6,j);
        s(1)=img(i+7,j);
        m=((s(1)*(2^7))+(s(2)*(2^6))+(s(3)*(2^5))+(s(4)*(2^4))+(s(5)*(2^3))+(s(6)*(2^2))+(s(7)*(2^1))+(s(8)*(2^0)));
        a=char(m);
        fprintf('%d',a);
        fprintf(',');
        
    end
    fprintf('},\n');
end
fprintf('\n};');
