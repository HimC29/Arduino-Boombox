import os
import shutil
from pathlib import Path

AUDIO_EXTS = (".mp3", ".wav")


def get_audio_files(folder):
    return sorted(
        f for f in os.listdir(folder)
        if f.lower().endswith(AUDIO_EXTS)
    )


def get_removable_mounts():
    mounts = []

    with open("/proc/mounts", "r") as f:
        for line in f:
            device, mountpoint, *_ = line.split()

            if not device.startswith("/dev/"):
                continue

            block = Path(device).name.rstrip("0123456789")
            removable = Path(f"/sys/block/{block}/removable")

            if removable.exists() and removable.read_text().strip() == "1":
                mounts.append(Path(mountpoint))

    return list(dict.fromkeys(mounts))


def select_sd_card():
    cards = get_removable_mounts()

    if not cards:
        print("❌ No removable SD cards detected")
        return None

    print("\n💾 Detected removable storage:")
    for i, card in enumerate(cards, 1):
        print(f"  {i}. {card}")

    while True:
        choice = input("\nSelect SD card number: ").strip()
        if choice.isdigit() and 1 <= int(choice) <= len(cards):
            return cards[int(choice) - 1]
        print("❌ Invalid selection")


def select_music_folder():
    default = Path.home() / "Music"

    print("\n📁 Music folder")
    print(f"Default: {default}")
    print("Press ENTER to use default, or type another path")

    user_input = input("\nFolder path: ").strip()
    folder = Path(user_input) if user_input else default

    if not folder.is_dir():
        print("❌ Folder not found")
        return None

    audio = get_audio_files(folder)
    if not audio:
        print("❌ No MP3 or WAV files found")
        return None

    print(f"✓ Found {len(audio)} audio files")
    return folder


def copy_files(src, sd_root):
    dst = sd_root / "01"
    dst.mkdir(exist_ok=True)

    existing = get_audio_files(dst)
    if existing:
        print(f"\n⚠️  Found {len(existing)} existing files in 01")
        if input("Delete them first? (yes/no): ").lower() == "yes":
            for f in existing:
                os.remove(dst / f)
            print("✓ Cleared existing files")

    audio = get_audio_files(src)

    print("\nFiles to be copied:")
    print("=" * 50)
    for i, f in enumerate(audio, 1):
        print(f"{i:3d}. {f}")
        if i == 10 and len(audio) > 10:
            print(f"... and {len(audio) - 10} more")
            break
    print("=" * 50)

    if input("\nProceed? (yes/no): ").lower() != "yes":
        print("❌ Cancelled")
        return

    print("\n📁 Copying files...\n")
    for i, f in enumerate(audio, 1):
        shutil.copy2(src / f, dst / f)
        print(f"✓ {i:3d}/{len(audio)} - {f}")

    print("\n✓ Done")
    print(f"🎵 Copied {len(audio)} files (original names preserved)")


def main():
    print("=" * 60)
    print("🎵 DFPlayer Mini SD Card Copier (Keep Names)")
    print("=" * 60)

    music = select_music_folder()
    if not music:
        return

    sd = select_sd_card()
    if not sd:
        return

    copy_files(music, sd)


if __name__ == "__main__":
    main()
