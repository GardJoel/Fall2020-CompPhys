clear;  
%clear out any previous definitions
data=load('q1.txt');
%import the data

f=figure;
%create a figure called f.

hold all
%the flag hold means we are going to add data to the plot, rather than replace data.  
% this is not necessary for this example, but may be needed when combining data.

set(f,'Visible','on');
set(gca, 'YScale', 'log');
set(gca, 'XScale', 'log');
%the chart will pop up if 'on' is selected.  You can use 'off' as well


plot(data(:,1),data(:,2:end),'.','MarkerSize',6,'color','black');
% This is the actual plot.  Only the first two aruments are required, the others optional.
% '.' refers to the plot markers being points.  You can use '+', for example.
% 'MarkerSize',1 choses the size of the plot markers
% 'color','black' choses the color.  

title('Derivative Estimate Deviation');
%writes to the top of the plot

box on
%puts a box all around the plot (instead of just x-y axes)

ax=gca;
% gca means "get current axes".  If you wnat to modify the axes, this is how.

ax.FontSize=12;
%sets the font size for the axes

xlabel('\Delta t');
ylabel('\delta (\Delta t)');
%labels the axes 

saveas(gcf,'q1','epsc');
%prints the figure to an eps file.  You should usually use eps instead of pdf if possible. 

hold off
