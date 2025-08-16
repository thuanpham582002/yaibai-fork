# Yabai Scripting Addition Installation Guide

This guide covers installing and troubleshooting the yabai scripting addition for advanced window management features.

## Prerequisites

- macOS with SIP (System Integrity Protection) disabled
- Yabai installed and working for basic operations
- Admin privileges for installation

## Installation Steps

### 1. Basic Installation

```bash
# Install scripting addition
sudo yabai --install-sa

# Load into current session
sudo yabai --load-sa
```

### 2. If Installation Fails with "could not locate Dock.app pid"

This is a common issue due to code signing. Follow these steps:

#### Step 1: Self-sign yabai binary
```bash
# Clean extended attributes
sudo xattr -cr /usr/local/bin/yabai

# Self-sign the binary
sudo codesign --force --deep --sign - /usr/local/bin/yabai
```

#### Step 2: Reinstall scripting addition
```bash
# Uninstall old version
sudo yabai --uninstall-sa

# Install with newly signed binary
sudo yabai --install-sa

# Load into Dock
sudo yabai --load-sa
```

#### Step 3: Verify installation
```bash
# Test space movement (requires scripting addition)
yabai -m space --move prev

# Should show proper error message instead of "scripting-addition failed"
```

### 3. Grant Accessibility Permissions

1. Open **System Preferences** → **Privacy & Security** → **Accessibility**
2. Click the **lock** and enter your password
3. Click **+** and add `/usr/local/bin/yabai`
4. Ensure yabai is **checked/enabled**

## Features Enabled by Scripting Addition

With the scripting addition installed, you can use:

- **Space Management**: Move, create, destroy spaces
- **Display Management**: Move spaces between displays
- **Advanced Window Operations**: Native fullscreen handling
- **Mission Control Integration**: Better space switching

### Commands that require scripting addition:
```bash
# Space movement
yabai -m space --move prev/next
yabai -m space --display 1/2

# Space creation/destruction  
yabai -m space --create
yabai -m space --destroy

# Advanced window operations
yabai -m window --space prev/next
yabai -m window --display 1/2
```

## Troubleshooting

### Issue: "scripting-addition failed to inject payload into Dock.app"

**Solution**: The yabai binary needs proper code signing.

1. Check current signing status:
   ```bash
   codesign -dv /usr/local/bin/yabai
   ```

2. If you see "adhoc" signature or signing errors, follow the self-signing steps above.

### Issue: "could not access accessibility features"

**Solution**: Grant accessibility permissions to yabai in System Preferences.

### Issue: Commands work but space movements fail

**Symptoms**: Basic yabai commands work, but space operations return errors.

**Solution**: 
1. Ensure scripting addition is loaded: `sudo yabai --load-sa`
2. Restart yabai service: `yabai --restart-service`
3. Check that Dock is running: `ps aux | grep Dock`

### Issue: Scripting addition stops working after system update

**Solution**: Reinstall after macOS updates:
```bash
sudo yabai --uninstall-sa
sudo yabai --install-sa  
sudo yabai --load-sa
```

## Automatic Loading

To automatically load the scripting addition on startup, add this to your `yabairc`:

```bash
# Add signal to reload scripting addition when Dock restarts
yabai -m signal --add event=dock_did_restart action="sudo yabai --load-sa"

# Load scripting addition on yabai start (optional)
sudo yabai --load-sa 2>/dev/null || echo "Note: Run 'sudo yabai --load-sa' manually if needed"
```

## Verification

After installation, verify everything works:

```bash
# Test basic space operations
yabai -m space --create
yabai -m space --destroy

# Test window movement
yabai -m window --space next
yabai -m window --space prev

# Test display movement (if you have multiple displays)
yabai -m space --display 2
yabai -m space --display 1
```

## Security Notes

- The self-signing process creates a local certificate for code signing
- This allows yabai to inject into system processes like Dock.app
- The signature is only valid on your local machine
- After system updates, you may need to re-sign and reinstall

## Related Files

- Scripting addition location: `/Library/ScriptingAdditions/yabai.osax/`
- Yabai binary: `/usr/local/bin/yabai` (or `/opt/homebrew/bin/yabai`)
- Service file: `~/Library/LaunchAgents/com.koekeishiya.yabai.plist`