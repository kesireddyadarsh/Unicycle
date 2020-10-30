clear all;
clc;
close all;

%read_1 = importdata('/home/ak/Documents/gccProjects/Unicycle/Unicycle_Location_70_0_2.txt');
%read_2 = importdata('/home/ak/Documents/gccProjects/Unicycle/Location_150_0_1.txt');
%read_3 = importdata('/home/ak/Documents/gccProjects/Unicycle/Location_120_0_2.txt');

reward_1 = importdata('/home/ak/Documents/gccProjects/Unicycle/rewards_0.txt');
reward_100 = importdata('/home/ak/Documents/gccProjects/Unicycle/rewards_1000.txt');
reward_150 = importdata('/home/ak/Documents/gccProjects/Unicycle/rewards_1600.txt');

temp = 6;
mean_1 = mean(reward_1(:,temp))
min(reward_1(:,temp))
mean_100 = mean(reward_100(:,temp))
min(reward_100(:,temp))
mean_150 = mean(reward_150(:,temp))
min(reward_150(:,temp))
%scatter(read_1(:,2),read_1(:,3))
%hold on;