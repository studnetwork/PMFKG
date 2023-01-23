import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AuthenticatedGuard } from './core/guards/authenticated.guard';
import { UnauthenticatedGuard } from './core/guards/unauthenticated.guard';
import { DashboardPageComponent } from './ui/pages/dashboard-page/dashboard-page.component';
import { LoginPageComponent } from './ui/pages/login-page/login-page.component';
import { ProfilePageComponent } from './ui/pages/profile-page/profile-page.component';
import { RegisterPageComponent } from './ui/pages/register-page/register-page.component';

const routes: Routes = [{
  path: 'register',
  component: RegisterPageComponent,
  canActivate: [UnauthenticatedGuard]
}, {
  path: 'login',
  component: LoginPageComponent,
  canActivate: [UnauthenticatedGuard]
}, {
  path: 'profile',
  component: ProfilePageComponent,
  canActivate: [AuthenticatedGuard]
}, {
  path: '',
  pathMatch: 'full',
  component: DashboardPageComponent
}, {
  path: '**',
  redirectTo: ''
}];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
