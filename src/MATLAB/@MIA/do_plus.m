function C= do_plus(A,B,permute_idx)
%perform addition based on the permutation idx of B

if(isa(B,'SparseMIA')) %if B is a sparseMIA we can safely convert it to MIA because it's the same size as A
    B=MIA(B);
end

do_permute=true;
a_size=size(A);
if numel(a_size)==2
    if a_size(2)==1;
        do_permute=false;
    end
end

if do_permute
    
    B_data=permute(B.data,permute_idx);
end

if(isa(B,'MIA'))
    C_data=A.data+B_data;
    C=MIA(C_data);
else
    error('Unsupported class in do_plus');
end
end
