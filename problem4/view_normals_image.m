function view_normals_image(image)
    %imshow(image);
    
    image_gray = rgb2gray(image);
    [tot_row, tot_col] = size(image_gray);
    imshow(image_gray);
    
    count = tot_col * tot_row;
	normals = zeros(tot_row, tot_col, 3);
   
    
    for i=1:1:tot_row
        for j=1:1:tot_col
            P = [i j];
            
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
            x = double(r/255);
            y = double(g/255);
            z = (1-x^2-y^2);
            normals(i, j, 1) = x;
            normals(i, j, 2) = y;
            normals(i, j, 3) = z;
            %normals(i, j) = normals(i,j)/norm(normals(i,j))
            %normals = [normals; [x y z]];
        end
    end
    
    
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
    val = get(hSlider, 'Value');
    
    light = [ col-c_col, c_row-row, val];
    %length = sqrt(light(1)*light(1)+light(2)*light(2)+light(3)*light(3));
    %light(1) = double(light(1)/length);
    %light(2) = double(light(2)/length);
    %light(3) = double(light(3)/length);
    light = light/norm(light)
    for i=1:1:tot_row
        for j=1:1:tot_col
			%index = 3*count;
			%n = [normals(index+1) normals(index+2) normals(index+3)];
	    	image_gray(i, j) = 255 * (light(1)*normals(i,j,1) + light(2)*normals(i,j,2) + light(3)*normals(i,j,3));
        end
    end
    
    frame = image_gray;
    set(imageHandle, 'CData', frame);
    
    drawnow
    
end
