-- Function to map with nnoremap,inoremap ...
local function map(mode, lhs, rhs, opts)
	local options = { noremap = true }
	if opts then
		options = vim.tbl_extend("force", options, opts)
	end
	vim.api.nvim_set_keymap(mode, lhs, rhs, options)
end

-- Keymaps to switch splits better
vim.keymap.set('n', '<C-h>', '<C-w>h')
vim.keymap.set('n', '<C-j>', '<C-w>j')
vim.keymap.set('n', '<C-k>', '<C-w>k')
vim.keymap.set('n', '<C-l>', '<C-w>l')

-- Keymaps to toggle neoterm
map('n', '<c-t>', ':Ttoggle<CR>')
map('i', '<c-t>', '<Esc>:Ttoggle<CR>')
map('t', '<c-t>', '<c-\\><c-n>:Ttoggle<CR>')

-- Spell-check keymap
vim.keymap.set({'n','v'}, '<leader>o', ':setlocal spell! spelllang=en_us<CR>')

-- Preform dot commands over visual blocks
vim.keymap.set('v', '.', ':normal .<CR>')

-- Replace all alias
vim.keymap.set('n', 'S', ':%s//g<left><left>')

-- Compile text using the compiler bash-script
vim.keymap.set('n', '<leader>c', ':w! | !compiler "%:p"<CR>')

-- Open corresponding .pdf/.html or preview
vim.keymap.set('n', '<leader>p', ':!opout "%:p"<CR>')

-- Save file as sudo on files that require root permissions
vim.keymap.set('c', 'w!!', 'execute ":silent! write !sudo tee % >/dev/null" | edit!<CR>')
