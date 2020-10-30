clear all;
clc;
close all;

read_1 = importdata('/home/ak/Documents/gccProjects/Unicycle/Unicycle_Location_380_0_1.txt');
%read_2 = importdata('/home/ak/Documents/gccProjects/Unicycle/Location_150_0_1.txt');
%read_3 = importdata('/home/ak/Documents/gccProjects/Unicycle/Location_120_0_2.txt');

scatter(read_1(:,2),read_1(:,3))
%hold on;