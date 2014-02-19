function example_gui( )

% Thanks to:
%   http://stackoverflow.com/questions/10853633/fast-way-to-update-image-objects-in-matlab-figure
%   http://stackoverflow.com/questions/13782842/get-the-coordinate-of-a-pixel-by-clicking-on-it-in-matlab

image = zeros(500,500);

%create an image 
imshow(image)
imageHandle = get(gca,'Children');

%create a slider
hSlider = uicontrol('Style', 'slider','Min',1,'Max',400,'Value',51,'Position', [400 20 220 20]);

%create callback functions for changes
change_callback_function = {@image_cick,imageHandle,hSlider,image};

%and call it when the slider changed
set(hSlider, 'Callback',change_callback_function)

%and when the image pressed on
set(imageHandle,'ButtonDownFcn', change_callback_function);
end

function image_cick(~, ~, imageHandle,hSlider,image)

    %Get the row, col location of the current mouse down
    loc = get(gca,'Currentpoint');
    row = loc(1,2);
    col = loc(1,1);
     
    val = get(hSlider,'Value');


    frame = image;
    
    %Draw a line on the frame
    for ii = 1:ceil(val)
        frame(ceil(row) + ii,ceil(col) + ii) = 1;
    end
    
    %and reset the data
    set(imageHandle ,'CData',frame);
    
    %finaly, redraw.
    drawnow     
end