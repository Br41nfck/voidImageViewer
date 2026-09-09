# TODO

## UI & Display
- [ ] Add UI option for config_title_bar_format
- [ ] Option to show full path like MPC
- [ ] Borderless window with retractable title bar
- [ ] Dark mode (system theme support)
- [ ] Dark skin (use system theme)
- [ ] High DPI icons
- [ ] Control toolbar customization
- [ ] Keep window aspect size option
- [ ] No minimum window size restriction

## Image Rendering
- [ ] Fix screen buffer mangling when resizing/auto-fitting
- [ ] Maintain correct aspect ratio when window clipped on auto size
- [ ] Use Direct3D for image rendering when shrinking
- [ ] OpenGL renderer
- [ ] Direct3D renderer
- [ ] Fix zoom issue: small image 64x64 → fullscreen should disable zoom
- [ ] Copy zoomed part to buffer to avoid GDI issues at high zoom
- [ ] Graphics::GetHalftonePalette for 256 color mode

## Zoom & Navigation
- [ ] Set/get zoom level via IPC
- [ ] Change zoom in/out in 1/10/100% steps
- [ ] Auto zoom: fit width, fit height, zoom inside, zoom outside
- [ ] Option to keep custom zoom level when image changes
- [ ] Left mouse drag: move window (zoom inside) or move image (other modes)
- [ ] When panning, clamp to image edge (not center)
- [ ] Shift+Ctrl+Numpad arrows for faster/slower movement

## Keyboard & Mouse
- [ ] Ctrl+C to copy display area to clipboard
- [ ] Ctrl+V to paste image from clipboard
- [ ] Middle mouse: scroll to control slideshow speed
- [ ] Keyboard shortcut to toggle randomize

## File Operations
- [ ] Undo delete (re-add image to playlist)
- [ ] Auto-update image when file changes on disk
- [ ] Next/previous with subfolder support
- [ ] Open/edit image with external app
- [ ] Paste DIB from clipboard (CF_DIB)

## Playlist & Slideshow
- [ ] Create playlist file format (image album)
- [ ] Image playlists (m3u, efu, txt support)
- [ ] Generate shuffle list for randomize option
- [ ] Ken Burns Effect Slideshows with FFmpeg
- [ ] "Play All Instances" option

## IPC & Piping
- [ ] Get image width/length via IPC
- [ ] Get/set display area width/length via IPC
- [ ] Set/get zoom level via IPC
- [ ] Set/get displayed image filename
- [ ] Support piping for ImageMagick/GraphicsMagick (stdin/stdout)
- [ ] Custom executable hooks on file change

## Installation
- [ ] MSI installer
- [ ] ARM/ARM64 installer
- [ ] Current user only install (%LocalAppData%\Programs)
- [ ] Compile on MinGW
- [ ] Fix delete crashes on Win9x

## Window Management
- [ ] Snap window to other windows and monitor borders
- [ ] Show on monitor with cursor (like MPC-HC)
- [ ] Make VIV aware of other VIV windows (cascade/tile support)
- [ ] "Touch window from inside" option

## File Association
- [ ] Install BMP/JPG only if default (avoid replacing non-default)

## Localization & Context Menu
- [ ] String table for localization
- [ ] Right-click → proper context menu (CDefFolderMenu_Create2)

## Command Line & Special Features
- [ ] Support named instances (viv.exe -no-new-instance)
- [ ] Load folder: voidImageViewer.exe "\my documents"
- [ ] Open filename "clipboard:" or "stdin:"
- [ ] Use sort order from Windows Explorer

## Color & ICC
- [ ] Color correction, white balance, sharpening
- [ ] Check ICC profile usage

## Miscellaneous
- [ ] APNG support
- [ ] Remove/replace GetFileAttributesEx
- [ ] == mehdi
- [ ] Check ICC usage
- [ ] Therube note: folder loading behavior with wildcards