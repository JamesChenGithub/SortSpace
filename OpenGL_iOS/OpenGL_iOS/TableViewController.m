//
//  TableViewController.m
//  OpenGL_iOS
//
//  Created by AlexiChen on 2018/2/9.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "TableViewController.h"

@interface TableViewController ()

@property (nonatomic, strong) NSMutableArray *tableItems;

@end

@interface TableItem : NSObject

@property (nonatomic, copy) NSString *keyText;
@property (nonatomic, copy) NSString *segueIdentifier;


@end

@implementation TableItem


@end

@implementation TableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.tableItems = [NSMutableArray array];
    
    TableItem *item = [[TableItem alloc] init];
    item.keyText = @"测试自定义OpenGLView";
    item.segueIdentifier = @"FirstViewController";
    
    [self.tableItems addObject:item];
    
    
    item = [[TableItem alloc] init];
    item.keyText = @"测试顶点着色器";
    item.segueIdentifier = @"SecondViewController";
    [self.tableItems addObject:item];
    
    item = [[TableItem alloc] init];
    item.keyText = @"OpenGL Draw Base";
    item.segueIdentifier = @"ThirdViewController";
    [self.tableItems addObject:item];
    
    
    item = [[TableItem alloc] init];
    item.keyText = @"OpenGL Draw Line";
    item.segueIdentifier = @"LineViewController";
    [self.tableItems addObject:item];
    
    
    item = [[TableItem alloc] init];
    item.keyText = @"OpenGL Draw Graphic";
    item.segueIdentifier = @"TrangleViewController";
    [self.tableItems addObject:item];
    
    
    item = [[TableItem alloc] init];
    item.keyText = @"OpenGL dynamic draw Graphic";
    item.segueIdentifier = @"GraphViewController";
    [self.tableItems addObject:item];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return self.tableItems.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell" forIndexPath:indexPath];
    
    TableItem *item = self.tableItems[indexPath.row];
    cell.textLabel.text = [item keyText];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    TableItem *item = self.tableItems[indexPath.row];
    [self performSegueWithIdentifier:item.segueIdentifier sender:nil];
}

/*
 // Override to support conditional editing of the table view.
 - (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the specified item to be editable.
 return YES;
 }
 */

/*
 // Override to support editing the table view.
 - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
 if (editingStyle == UITableViewCellEditingStyleDelete) {
 // Delete the row from the data source
 [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
 } else if (editingStyle == UITableViewCellEditingStyleInsert) {
 // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
 }   
 }
 */

/*
 // Override to support rearranging the table view.
 - (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
 }
 */

/*
 // Override to support conditional rearranging of the table view.
 - (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the item to be re-orderable.
 return YES;
 }
 */

/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

@end
