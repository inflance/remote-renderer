import os
import subprocess
import zipfile
import urllib.request
from tqdm import tqdm

# 设置 vcpkg 的下载链接和版本
vcpkg_url = "https://codeload.github.com/microsoft/vcpkg/zip/refs/tags/2023.11.20"

# 设置解压路径
vcpkg_root = "C:/vcpkg"

# 下载 vcpkg 压缩包
download_path = "vcpkg.zip"

# 添加下载进度条
with tqdm(unit="B", unit_scale=True, unit_divisor=1024, miniters=1, desc="Downloading") as t:
    urllib.request.urlretrieve(vcpkg_url, download_path, reporthook=lambda blocks, block_size, total_size: t.update(blocks * block_size))

# 解压 vcpkg
with zipfile.ZipFile(download_path, 'r') as zip_ref:
    zip_ref.extractall(vcpkg_root)

# 删除下载的压缩包
os.remove(download_path)

# 设置 VCPKG_ROOT 环境变量
os.environ["VCPKG_ROOT"] = vcpkg_root

# 打印成功信息
print("vcpkg 安装成功，并设置 VCPKG_ROOT 为:", vcpkg_root)

try:
    # 在此处可以继续执行其他与 vcpkg 相关的操作，例如安装库等
    # 例如，运行 vcpkg install <package-name>
    subprocess.run(["vcpkg", "install", "<package-name>"])
except subprocess.CalledProcessError as e:
    # 打印详细错误信息
    print("命令执行失败，错误信息:", e)

# 等待用户按下 Enter 键
input("Press Enter to exit...")
