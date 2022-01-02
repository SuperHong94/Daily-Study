using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DataBinding
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            Emp e = new Emp()
            {
                Ename = "홍길동",
                City = "서울"
            };

            this.DataContext = e;
        }

        private void OnClicked(object sender, RoutedEventArgs e)
        {
            Emp emp = this.DataContext as Emp;
            MessageBox.Show(emp.Ename + " " + emp.City);
        }
    }
}
