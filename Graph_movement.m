clear all;
clc;
close all;

read_1 = importdata('/home/ak/Documents/gccProjects/Unicycle/Location_1600_0_0.txt');
read_2 = importdata('/home/ak/Documents/gccProjects/Unicycle/Location_1600_0_1.txt');
read_3 = importdata('/home/ak/Documents/gccProjects/Unicycle/Location_1600_0_2.txt');

time_step = 2000;
data_1 = zeros(time_step, 3);
data_2 = zeros(time_step, 3);
data_3 = zeros(time_step, 3);
team_number = 4;
loop_number = 1;
for temp = 1:size(read_1)
  if read_1(temp,1) == team_number
    data_1(loop_number, 1) = read_1(temp,1);
    data_1(loop_number, 2)  = read_1(temp,2);
    data_1(loop_number, 3)  = read_1(temp,3);
    loop_number = loop_number + 1;
  endif
endfor

loop_number = 1;
for temp = 1:size(read_2)
  if read_2(temp,1) == team_number
    data_2(loop_number, 1) = read_2(temp,1);
    data_2(loop_number, 2)  = read_2(temp,2);
    data_2(loop_number, 3)  = read_2(temp,3);
    loop_number = loop_number + 1;
  endif
endfor

loop_number = 1;
for temp = 1:size(read_3)  
  if read_3(temp,1) == team_number
    data_3(loop_number, 1) = read_3(temp,1);
    data_3(loop_number, 2)  = read_3(temp,2);
    data_3(loop_number, 3)  = read_3(temp,3);
    loop_number = loop_number + 1;
    endif  
endfor


axh = axes();
hold(axh,'on');
%axis([-2 500 -2 12]);
%for i = 1:size(data_1)
  scatter(data_1(:,2),data_1(:,3),300,'r','filled','d')
  %plot(data_1(i,2),data_1(i,3),300,'r')
  %pause(0.5)
  scatter(data_2(:,2),data_2(:,3),300,'b','filled','d')
  %plot(data_2(i,2),data_2(i,3),300,'b')
  %pause(0.5)
  scatter(data_3(:,2),data_3(:,3),300,'g','filled','d')
  %plot(data_3(i,2),data_3(i,3),300,'g')
  %drawnow;
  %pause(0.5)
%endfor
%line1 = scatter(axh,data_1(:,2), data_1(:,3),'-','Color','r');
%marker1 = plot(axh,2,0,'o','Color','r');
%disp(team_number)
%disp(data_1(3,2))
%scatter(data_1(:,2),data_1(:,3))
%hold on;
%scatter(data_2(:,2),data_2(:,3))
%hold on;
%scatter(data_3(:,2),data_3(:,3))
%hold on;
%marker1.XData = data_1(k,2);
%marker1.YData = data_1(k,3);
%line1.YData(1:k) = y(1:k);
%drawnow();

