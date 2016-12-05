function DisplaySuperpixel(label,img,name)

[nRows,nCols,~]=size(img);
   for m=1:nRows
        for n=1:nCols
            L=label(m,n);
            count=0;
            minx=max(m-1,1);
            maxx=min(m+1,nRows);
            miny=max(n-1,1);
            maxy=min(n+1,nCols);
            for u=minx:maxx;
                for v=miny:maxy
                    if(label(u,v)~=L)
                        count=count+1;
                    end
                    if(count==2)
                        break;
                    end
                end
                if(count==2)
                    break;
                end
            end
            if(count==2)
                img(m,n,:)=0;
            end
        end
    end
figure;
imshow(img);
imwrite(img,[name,'result.bmp'],'bmp')

fid=fopen([name,'.txt'],'wt');%写入文件路径
[m,n]=size(label);
 for i=1:1:m
    for j=1:1:n
       if j==n
         fprintf(fid,'%g\n',label(i,j));
      else
        fprintf(fid,'%g\t',label(i,j));
       end
    end
end
fclose(fid);
end
