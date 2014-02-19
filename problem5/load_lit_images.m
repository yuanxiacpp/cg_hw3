function [ output ] = load_lit_images( filename )
%%LOAD_LIT_IMAGES Loads lit images in our format
%  This function loads all the images in a dataset retruns them in a struct
%  array. 
%  For example, 
%   load_lit_images( 'data_479/data_479.mat' )
%  will load the dataset that we provided with this assignment.
%  The output will be a struct array, each element of the array will have
%  two diffent atributes:
%       vector - the location of the light
%       image  - image of the object being lit from that direction
%
%  Example usage:
%      imlist = load_lit_images('data_479/data_479.mat')
%      for ii = 1:length(imlist)
%           figure()
%           disp(imlist(ii).vector)
%           imshow(imlist(ii).image)
%       end

%%
[pathstr,~,~] = fileparts(filename);

data = load(filename);


for ii = 1:length(data(1).light_data)
    output(ii).vector = data(1).light_data(ii).vector;
    output(ii).image = imread(fullfile(pathstr,data(1).light_data(ii).file_name));
end


end

