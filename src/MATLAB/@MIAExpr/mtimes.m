function CExpr = mtimes(A,B)
%MIA multiplication
%performs multiplication using MIA algebra, e.g., A('ij!k')*B('jl!k'),
%which is an outer product across i and l, inner product across j, and
%inter (element-wise) product across k. Any other combination is possible,
%provided number of indices equals MIA order and dimensions match up
%appropriately. Resulting MIAExpr contains MIA and indices equivalent to:
%[a_outer_indices, b_outer_indices, inter_indices]. For example, in above
%, if you do ans=A('ij!k')*B('jl!k') you will get an MIAExpr holding an
%MIA and indices equivalent to C('ilk')=A('ij!k')*B('jl!k'). To use
%different assignment indices, use an already constructed MIA, e.g., 
%C=MIA;
%C('kil')=A('ij!k')*B('jl!k')
%or
%C('lik')=A('ij!k')*B('jl!k')
%or any other legal index set.

[a_inner_idx, a_inter_idx, a_outer_idx, b_inner_idx, b_inter_idx, b_outer_idx]=pull_mult_indices(A,B);
error_check_mult(A,B,a_inner_idx, a_inter_idx, b_inner_idx, b_inter_idx) %make sure indices match up properly for multiplication



A_mia=A.m_mia;
B_mia=B.m_mia;
a_size=size(A_mia);
b_size=size(B_mia);



%extract index ranges for A and B. Also calculate ranges after A and B are
%flattened into lattices
a_inter_size=a_size(a_inter_idx);
a_outer_size=a_size(a_outer_idx);
b_outer_size=b_size(b_outer_idx);


A_lat=A_mia.toLattice(a_outer_idx, a_inner_idx, a_inter_idx);
B_lat=B_mia.toLattice(b_inner_idx, b_outer_idx, b_inter_idx);



%perform lattice product
C_lat=A_lat*B_lat;
clear A_lat B_lat
%convert result back to an MIA
c_indices=A.m_indices(a_outer_idx);
c_indices=[c_indices B.m_indices(b_outer_idx)];
c_indices=[c_indices A.m_indices(a_inter_idx)];

C=C_lat.toMIA(a_outer_size, b_outer_size, a_inter_size);
%create a MIAExpr using resulting MIA and indices
CExpr=MIAExpr(C,c_indices);


end

