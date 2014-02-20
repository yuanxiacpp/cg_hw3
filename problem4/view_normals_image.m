function view_normals_image(image)
    %imshow(image)
    
    image_gray = rgb2gray(image);
    [tot_row, tot_col] = size(image_gray);
    imshow(image_gray);
    
    normals = zeros(tot_row, tot_col, 2);
    
    for i=1:1:tot_row
        for j=1:1:tot_col
            r = double(image(i, j, 1));
            g = double(image(i, j, 2));
            b = image(i, j, 3);
            if (b == 192)
                %b
                r = 0 - r;
                g = g;
            elseif (b == 128)
                r = -r;
                g = -g;
            elseif (b == 64)
                r = r; 
                g = g;
            else
                %b
                r = r;
                g = 0 - g;
            end
            r = r/255;
            g = g/255;
            normals(i, j, 1) = r;
            normals(i, j, 2) = g;
        end
    end
    
    size(normals)
    
    imageHandle = get(gca, 'Children');
    
    hSlider = uicontrol('Style', 'slider', 'Min', 1, 'Max', 400, 'Value', 51, 'Position', [400 20 220 20]);
    
    change_callback_function = {@image_cick, imageHandle, hSlider, normals, image_gray, tot_row, tot_col};
    
    set(hSlider, 'Callback', change_callback_function)
    set(imageHandle, 'ButtonDownFcn', change_callback_function);
    
end

function image_cick(~, ~, imageHandle, hSlider, normals, image_gray, tot_row, tot_col)
    c_row = tot_row / 2;
    c_col = tot_col / 2;
    loc = get(gca, 'Currentpoint');
    row = loc(1, 2);
    col = loc(1, 1);
    
    light = [col-c_col, c_row-row];
    length = sqrt(light(1)*light(1)+light(2)*light(2));
    light(1) = double(light(1)/length);
    light(2) = double(light(2)/length);
    light
    for i=1:1:tot_row
        for j=1:1:tot_col
            image_gray(i, j) = 255 * light(1)*normals(i,j,1)+light(2)*normals(i,j,2);
        end
    end
    
    frame = image_gray;
    set(imageHandle, 'CData', frame);
    
    drawnow
    
end