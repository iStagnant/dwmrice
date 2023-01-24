local knap = require('knap')

-- Processes the document once, and refreshes the view
vim.keymap.set('n', '<leader>lp', knap.process_once, { desc = '[L]atex [Preview]' })

-- Closes the viewer application, and allows settings to be reset
vim.keymap.set('n', '<leader>lc', knap.close_viewer, { desc = '[L]atex [C]lose viewer application' })

-- Toggles the auto-processing on and off
vim.keymap.set('n', '<leader>la', knap.toggle_autopreviewing, { desc = '[L]atex [A]utomatic preview' })

-- Invokes a SyncTeX forward search, or similar, where appropriate
vim.keymap.set('n', '<leader>lj', knap.forward_jump, { desc = '[L]atex [J]ump in viewer app' })

vim.g.knap_settings = {
    texoutputext = "pdf",
    textopdf = "pdflatex -synctex=1 -halt-on-error -interaction=batchmode %docroot%",
     textopdfviewerlaunch = "zathura --synctex-editor-command 'nvim --headless -es --cmd \"lua require('\"'\"'knaphelper'\"'\"').relayjump('\"'\"'%servername%'\"'\"','\"'\"'%{input}'\"'\"',%{line},0)\"' %outputfile%",
     textopdfviewerrefresh = "none",
     textopdfforwardjump = "zathura --synctex-forward=%line%:%column%:%srcfile% %outputfile%"
}
