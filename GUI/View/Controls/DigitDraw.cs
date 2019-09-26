using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI.Model;

namespace GUI.View.Controls
{
	/// <summary>
	/// Digit drawing area
	/// </summary>
	public partial class DigitDraw : UserControl
	{
		Bitmap bitmap = new Bitmap(280, 280);
		bool isDown = false;

		public DigitDraw()
		{
			InitializeComponent();
			pictureBox.MouseDown += MouseClicked;
			pictureBox.MouseMove += MouseMoved;
			pictureBox.MouseUp += MouseReleased;
			pictureBox.Image = bitmap;
		}

		/// <summary>
		/// Returns drawn digit as input for network
		/// </summary>
		public List<float> DigitPixels
		{
			get
			{
				return ConvertBitmapToPixelList();
			}
		}

		/// <summary>
		/// Converts image to list of float values. Compresses image
		/// </summary>
		/// <returns></returns>
		private List<float> ConvertBitmapToPixelList()
		{
			Color[] pixels = new Color[DigitSet.DIGIT_SIZE * DigitSet.DIGIT_SIZE];
			int k = 0;
			for (int i = 0; i < 279; i += 10)
			{
				for (int j = 0; j < 279; j += 10)
				{
					pixels[k++] = bitmap.GetPixel(j, i);
				}
			}
			List<float> floatPixels = new List<float>();
			for (int i = 0; i < pixels.Length; i++)
			{
				if(pixels[i].A != 0)
				{
					floatPixels.Add(1.0f);
				}
				else
				{
					floatPixels.Add(0.0f);
				}
			}
			Smooth(floatPixels);
			return floatPixels;
		}

		/// <summary>
		/// Smooths digit image
		/// </summary>
		/// <param name="floatPixels"></param>
		private void Smooth(List<float> floatPixels)
		{
			int max = (int)DigitSet.DIGIT_SIZE;
			//Left smooth
			for (int row = 1; row < max - 1; row++)
			{
				for(int column = 1; column < max - 1; column++)
				{
					float val = 0f;
					if (floatPixels[row * max + column + 1] > val)
					{
						val = floatPixels[row * max + column + 1];
					}
					if(val / 2f > floatPixels[row * max + column])
					{
						floatPixels[row * max + column] = val / 2f;
					}
				}
			}
			//Right smooth
			for (int row = 1; row < max - 1; row++)
			{
				for (int column = max - 2; column > 0; column--)
				{
					float val = 0f;
					if (floatPixels[row * max + column - 1] > val)
					{
						val = floatPixels[row * max + column - 1];
					}
					if (val / 2f > floatPixels[row * max + column])
					{
						floatPixels[row * max + column] = val / 2f;
					}
				}
			}
			//Smooth up
			for (int column = 1; column < max - 1; column++)
			{
				for (int row = 1; row < max - 1; row++)
				{
					float val = 0f;
					if (floatPixels[(row + 1) * max + column] > val)
					{
						val = floatPixels[(row + 1) * max + column];
					}
					if (val / 2f > floatPixels[row * max + column])
					{
						floatPixels[row * max + column] = val / 2f;
					}
				}
			}
			//Smooth down
			for (int column = 1; column < max - 1; column++)
			{
				for (int row = max - 2; row > 0; row--)
				{
					float val = 0f;
					if (floatPixels[(row - 1) * max + column] > val)
					{
						val = floatPixels[(row - 1) * max + column];
					}
					if (val / 2f > floatPixels[row * max + column])
					{
						floatPixels[row * max + column] = val / 2f;
					}
				}
			}
		}

		/// <summary>
		/// Drawing started
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="mouseEventArgs"></param>
		private void MouseClicked(object sender, MouseEventArgs mouseEventArgs)
		{
			isDown = true;
		}

		/// <summary>
		/// Draws elipsis in place. Whien mouse is moved, a line is created
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="mouseEventArgs"></param>
		private void MouseMoved(object sender, MouseEventArgs mouseEventArgs)
		{
			if(isDown)
			{
				Graphics graphics = Graphics.FromImage(bitmap);
				graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
				Pen pen = new Pen(Brushes.Black, 14);
				graphics.DrawEllipse(pen, mouseEventArgs.Location.X, mouseEventArgs.Location.Y, 7, 7);
				graphics.Dispose();
				pictureBox.Image = bitmap;
			}
		}

		/// <summary>
		/// Drwaing ended
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="mouseEventArgs"></param>
		private void MouseReleased(object sender, MouseEventArgs mouseEventArgs)
		{
			isDown = false;
		}

		/// <summary>
		/// Clear drawn digit
		/// </summary>
		internal void ClearImage()
		{
			bitmap = new Bitmap(280, 280);
			pictureBox.Image = bitmap;
		}
	}
}
