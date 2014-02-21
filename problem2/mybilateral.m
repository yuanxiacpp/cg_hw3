function [base, detail] = mybilateral(input_image, spatial_radius, intensity_radius)
    gray = rgb2gray(input_image);
    [row, col] = size(gray);
    n = 3;
    d = zeros(n, n);
    
    cr = round(n/2);
    cc = round(n/2);
    
    base = input_image;
    
    for k=1:1:n
        for l=1:1:n
            d(k, l) = exp(-((cr-k)^2+(cc-l)^2)/(2*spatial_radius^2));
        end
    end
    
    
    for i=1:1:row
        for j=1:1:col
            r = double(zeros(n, n));
            for k=1:1:n
                for l=1:1:n
                    p = i + k - cr;
                    q = j + l - cc;

                    if (p < 1 | p > row | q < 1 | q > col)
                        r(k, l) = 0;
                    else
                        r(k, l) = exp((gray(i,j)-gray(p, q))^2/(2*intensity_radius^2));
                    end
                end
            end
            
            w = d * r;
            sum = double(0);
            for k=1:1:n
                for l=1:1:n
                    sum = sum + w(k,l);
                end
            end
            
            w = w/sum;
            
            newR = 0;
            newG = 0;
            newB = 0;
            for k=1:1:n
                for l=1:1:n
                    p = i+k-cr;
                    q = j+l-cc;
                    
                    if (p < 1 | p > row | q < 1 | q > col)
                        ;
                    else
                        newR = newR + input_image(p,q,1)*w(k,l);
                        newG = newG + input_image(p,q,2)*w(k,l);
                        newB = newB + input_image(p,q,3)*w(k,l);
                    end
                    
                end
            end
            
            base(i,j,1) = uint8(newR);
            base(i,j,2) = uint8(newG);
            base(i,j,3) = uint8(newB);
           
            
        end
    end
    
    detail = input_image - base;
end
