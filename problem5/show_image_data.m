function show_image_data( imlist )
%SHOW_IMAGE_DATA An example of how to use the data from the image list
% Use with show_image_data(load_lit_images('data_479/data_479.mat'))
% show_image_data(load_lit_images('data_579/data_579.mat'))


for ii = 1:length(imlist)
   figure()
   subplot(1,2,1)
   imshow(imlist(ii).image)
   subplot(1,2,2)
   quiver(0,0,imlist(ii).vector(1),imlist(ii).vector(2))
   xlim([-1,1]);
   ylim([-1,1]);
end

end

