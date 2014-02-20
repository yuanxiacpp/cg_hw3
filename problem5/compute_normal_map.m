function out = compute_normal_map(image_structure)

    [count, length] = size(image_structure);
    
    
    
    S = [];
    for i=1:1:length
        light = image_structure(i).vector;
        image_structure(i).gray = rgb2gray(image_structure(i).image);
        S = [S; light];
    end
    
    size(image_structure(i).gray)
    C = inv(S' * S) * S';
    
    [row, col] = size(S);
    [height, width, rgb] = size(image_structure(1).image)
    out = zeros(height, width, 3);
    for i=1:1:height
        for j=1:1:width
            I = [];
            for k=1:1:length
                %gray = rgb2gray(image_structure(k).image);
                I = [I; double(image_structure(k).gray(i, j))];
            end
            %I = I/norm(I);
            n = C * I;
            r = uint8(abs(n(1)));
            g = uint8(abs(n(2)));
            b = 0;
            if (n(1) < 0)
                b = b+128;
            end
            if (n(2) > 0)
                b = b+64;
            end
            out(i, j, 1) = r;
            out(i, j, 2) = g;
            out(i, j, 3) = b;
            
            
        end
    end
    
    
    
end