%======================================================================
% DBSCAN demo in TIP 2016
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % J. Shen, X. Hao, Z. Liang, Y. Liu, W. Wang, and L. Shao, 
% % Real-time Superpixel Segmentation by DBSCAN Clustering Algorithm, 
% % IEEE Trans. on Image Processing, 25(12):5933-5942, 2016 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Copyright (C) 2016  Beijing Laboratory of Intelligent Information Technology
% Any further questions, please send email to: shenjianbing@bit.edu.cn  or shenjianbingcg@gmail.com
%======================================================================
%Input parameters are: 
%[1] 8 bit images (color)
%[2] Number of required superpixels (optional, default is 200)
%[3] post processing(1 is need,0 is not)
%Ouputs are:
%[1] labels (in raster scan order)

%NOTES:
%[1] number of returned superpixels may be different from the input
%number of superpixels.
%[2] you should compile the cpp file using visual studio 2008 or later version
% -- mex DBscan_mex.cpp 
%======================================================================
clear all;
close all;
currentFolder = pwd;
addpath(genpath(currentFolder))
addpath('code');
addpath('imgs');
name='3096';
im = imread([name,'.jpg']);
post=1;
img = uint8(im);
number_superpixels =500;
tic; 
label = DBscan_mex(img,number_superpixels,post);
toc;
SuperpixelSave(label,im,name);
DisplaySuperpixel(label,im,name);
% end
